
#include "lddsbus.h"

#include "appconfig.h"

struct LDdsBusPrivate
{


};

LDdsBus::LDdsBus()
{
}

LDdsBus::~LDdsBus()
{
}

QByteArray LDdsBus::serializeVariant(const QVariant & variant)
{
    QByteArray  byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << variant; // –¥»Î QVariant
    return byteArray;
}

QVariant LDdsBus::deserializeVariant(const QByteArray & byteArray)
{
    QVariant    variant;
    QDataStream stream(byteArray);
    stream >> variant; // ∂¡»° QVariant
    return variant;
}

void LDdsBus::createDomain(unsigned int domain /*= 0*/)
{

}

void LDdsBus::destroyDomain(unsigned int domain /*= 0*/)
{
}

int LDdsBus::subscribeTopic(const QString & event, const char * slotName, QObject * obj)
{
    return -1;
}

void LDdsBus::publishTopic(const QString & event, const QVariant & var)
{
}

void LDdsBus::getFindsetList()
{
}

void LDdsBus::unSubscribeTopic(int subStub /*= 0*/)
{
}
