#include <QDebug>
#include "leventbus.h"

// 全局变量，确保在 main 函数执行之前初始化
// LEventBus & globalEventBus = LEventBus::instance();
LEventBus & LEventBus::instance()
{
    static LEventBus instance;
    return instance;
}

void LEventBus::subscribe(const QString & event, const char * slotName, QObject * obj)
{
    qDebug() << slotName;
    std::lock_guard<std::mutex> lock(m_mutex);

    // 将事件与回调信息绑定，保存槽函数名和对象
    m_callbacks[event].push_back({obj, slotName});
}

void LEventBus::publish(const QString & event, const QVariant & var)
{
    m_eventQueue.enqueue(qMakePair(event, var));
	return;
	    {
        QPair<QString, QVariant> eventPair;
        if (m_eventQueue.dequeue(eventPair))
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            auto                        it = m_callbacks.find(eventPair.first);

            if (it != m_callbacks.end())
            {
                // 发射事件，通过 invokeMethod 调用订阅者的槽
                for (const CallbackInfo & callbackInfo : it->second)
                {
                    // 动态调用每个订阅者的槽函数
                    QMetaObject::invokeMethod(callbackInfo.obj,
                                              callbackInfo.slotName, // 使用实际的槽函数名
                                              Qt::QueuedConnection,  // 在目标线程执行
                                              Q_ARG(int, 1),
                                              Q_ARG(int, 2));
                }
            }
        }
    }
}

void LEventBus::run()
{
	qDebug()<<"事件队列线程id:"<<QThread::currentThreadId();
	//return;
    // 执行事件循环
     while (!isInterruptionRequested())
    {
        QPair<QString, QVariant> eventPair;
        if (m_eventQueue.dequeue(eventPair))
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            auto                        it = m_callbacks.find(eventPair.first);

            if (it != m_callbacks.end())
            {
                // 发射事件，通过 invokeMethod 调用订阅者的槽
                for (const CallbackInfo & callbackInfo : it->second)
                {
                    // 动态调用每个订阅者的槽函数
                    QMetaObject::invokeMethod(callbackInfo.obj,
                                              callbackInfo.slotName, // 使用实际的槽函数名
                                              Qt::QueuedConnection,  // 在目标线程执行
                                               Q_ARG(int,1),
                                              Q_ARG(int, 2));
                }
            }
        }
    }
}

LEventBus::LEventBus()
{
    start();
}

LEventBus::~LEventBus()
{
    m_eventQueue.stop();
    requestInterruption();
    wait();
}