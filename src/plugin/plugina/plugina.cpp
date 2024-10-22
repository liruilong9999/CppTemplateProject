#include <QDebug>
#include <lib/appskeleton/ipluginview.h>
#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <QThread>

#include <lib/leventbus/leventbus.h>
#include <lib/llog/llog.h>

#include <common/CircularQueue.h>

#include "plugina.h"
#include "testclass.h"

PluginA::PluginA(QObject * parent)
    : QObject(parent)
{
}

QString PluginA::getname()
{
    return QString("插件A");
}

// 定义处理数据的回调函数
void myCallback(const QVariant & data)
{
    // 假设我们知道 data 是一个 int
    if (data.canConvert<int>())
    {
        int intValue = data.toInt();
        std::cout << "Received Integer: " << intValue << std::endl;
    }
    // 如果需要处理其他类型，可以继续添加相应的逻辑
    qDebug()<<"子线程id:"<<QThread::currentThreadId();
}

bool PluginA::init()
{
    m_TestClass       = new TestClass;
    m_actionTestClass = new QAction(QString("按钮1"));
    if (m_actionTestClass)
    {
        connect(m_actionTestClass, &QAction::triggered, this, &PluginA::addTestClass);
        IPluginView::getInstance().registerAction(QString("组"), QString("页"), m_actionTestClass);
    }

    qDebug() << "主线程id:" << QThread::currentThreadId();
    LEventBus::instance().subscribe("testEvent", myCallback);

    // 发布一个数据
    QVariant data(42); // QVariant 中存储整数
    LEventBus::instance().publish("testEvent", data);

    return true;
}

bool PluginA::clean()
{
    return true;
}

void PluginA::addTestClass()
{
    if (m_TestClass)
    {
    }
}
