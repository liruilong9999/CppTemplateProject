#include <ddscxx/dds/dds.hpp>

#include <lbase/appconfig.h>
#include <lbase/lbase.h>

#include <vector>

#include "lddsbus.h"
#include "dataTrans.hpp"

using namespace org::eclipse::cyclonedds;

uint32_t g_getDomainID_1()
{
    uint32_t initDomainID = domain::default_id();
    QString  id           = QString::number(initDomainID);
    return AppConfig::getInstance()->getAppConfig("root.domainid1.data", id).toUInt();
};

uint32_t g_getDomainID_2()
{
    uint32_t initDomainID = domain::default_id();
    QString  id           = QString::number(initDomainID + 1);
    return AppConfig::getInstance()->getAppConfig("root.domainid2.data", id).toUInt();
};

struct DomainInfo
{
    DomainInfo()
        : participantTrans(g_getDomainID_1())
        , participantPlayback(g_getDomainID_2())
        , topicTrans(participantTrans, "MyModule_MyData_Msg")
        , publisherTrans(participantTrans)
        , writerTrans(publisherTrans, topicTrans)
        , subscriberTrans(participantTrans)
        , readerTrans(subscriberTrans, topicTrans)

        , topicPlayback(participantPlayback, "MyModule_MyData_Msg")
        , publisherPlayback(participantPlayback)
        , writerPlayback(publisherPlayback, topicPlayback)
        , subscriberPlayback(participantPlayback)
        , readerPlayback(subscriberPlayback, topicPlayback)
    {
    }

    uint32_t domainIdTrans()
    {
        return participantTrans.domain_id();
    }
    uint32_t domainIdPlayback()
    {
        return participantPlayback.domain_id();
    }
    dds::domain::DomainParticipant         participantTrans; // 域名参与者(态势显示域)
    dds::topic::Topic<MyModule::MyData>    topicTrans;       // 主题(态势显示域)
    dds::pub::Publisher                    publisherTrans;   // 发布者(态势显示域)
    dds::pub::DataWriter<MyModule::MyData> writerTrans;      // 数据写入器(态势显示域)
    dds::sub::Subscriber                   subscriberTrans;  // 接收者(态势显示域)
    dds::sub::DataReader<MyModule::MyData> readerTrans;      // 数据读取器(态势显示域)

    dds::domain::DomainParticipant         participantPlayback; // 域名参与者(回放域)
    dds::topic::Topic<MyModule::MyData>    topicPlayback;       // 主题(回放域)
    dds::pub::Publisher                    publisherPlayback;   // 发布者(回放域)
    dds::pub::DataWriter<MyModule::MyData> writerPlayback;      // 数据写入器(回放域)
    dds::sub::Subscriber                   subscriberPlayback;  // 接收者(回放域)
    dds::sub::DataReader<MyModule::MyData> readerPlayback;      // 数据读取器(回放域)
};

struct LDdsBusPrivate
{
    DomainInfo domainInfo; // 域信息
};

void ddsPublishTopic(QString event, QVariant var)
{
    LDdsBus::instance().publishTopic(event, var);
}

LDdsBus::LDdsBus()
    : m_pPrivate(new LDdsBusPrivate)
{
    start();
}

LDdsBus::~LDdsBus()
{
    requestInterruption();
    wait();

    if (m_pPrivate)
    {
        delete m_pPrivate;
        m_pPrivate = nullptr;
    }
}

LDdsBus & LDdsBus::instance()
{
    static LDdsBus instance;
    return instance;
}

QByteArray LDdsBus::serializeVariant(const QVariant & variant)
{
    QByteArray  byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    // 设置为小端字节序
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << variant; // 序列化 QVariant
    return byteArray;
}

QVariant LDdsBus::deserializeVariant(const QByteArray & byteArray)
{
    QVariant    variant;
    QDataStream stream(byteArray);
    // 设置为小端字节序
    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> variant; // 反序列化 QVariant
    return variant;
}

int LDdsBus::subscribeTopic(QString event, char * slotName, QObject * obj)
{
    return -1;
}

void LDdsBus::publishTopic(QString event, QVariant var)
{
    std::string          stdString1     = event.toStdString();
    QByteArray           serializedData = serializeVariant(var);
    std::vector<uint8_t> dataVector(serializedData.begin(), serializedData.end());
    MyModule::MyData     msg(stdString1, dataVector);

    if (m_displaySate == DisplayModelState::RunningState)
    {
        // 写入
        m_pPrivate->domainInfo.writerTrans.write(msg);
    }
    else if (m_displaySate == DisplayModelState::PlayBackState)
    {
        // 写入
        m_pPrivate->domainInfo.writerPlayback.write(msg);
    }
    else
    {
    }
}

void LDdsBus::getFindsetList()
{
}

void LDdsBus::unSubscribeTopic(int subStub /*= 0*/)
{
}

DisplayModelState LDdsBus::getDisplayModelState()
{
    return m_displaySate;
}

void LDdsBus::setDisplayModelState(DisplayModelState model)
{
    m_displaySate = model;
}

void LDdsBus::run()
{
    while (!isInterruptionRequested())
    {
        dds::sub::LoanedSamples<MyModule::MyData> samples;

        {
            // 共享锁用于只读操作
            std::shared_lock<std::shared_mutex> lock(m_sharedMutex);

            if (m_displaySate == DisplayModelState::RunningState)
            {
                samples = m_pPrivate->domainInfo.readerTrans.take();
            }
            else if (m_displaySate == DisplayModelState::PlayBackState)
            {
                samples = m_pPrivate->domainInfo.readerPlayback.take();
            }
        } // 自动解锁

        if (samples.length() > 0)
        {
            dds::sub::LoanedSamples<MyModule::MyData>::const_iterator sample_iter;
            for (sample_iter = samples.begin(); sample_iter < samples.end(); ++sample_iter)
            {
                const MyModule::MyData &     msg  = sample_iter->data();
                const dds::sub::SampleInfo & info = sample_iter->info();

                if (info.valid())
                {
                    // 从 MyData 中提取数据
                    QString    topic = QString::fromStdString(msg.topicName1()); // 提取 topicName1
                    QByteArray dataArray(reinterpret_cast<const char *>(msg.dataSeg1().data()), int(msg.dataSeg1().size()));

                    // 反序列化 dataSeg1，得到 QVariant
                    QVariant dataVariant = deserializeVariant(dataArray);

                    // 发布数据到事件总线
                    LEventBus::instance().publish(topic, dataVariant);
                }
            }
        }
    }
}
