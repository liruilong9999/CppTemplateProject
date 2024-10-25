#include <QDebug>
#include "leventbus.h"

// 全局变量，确保在 main 函数执行之前初始化
// LEventBus & globalEventBus = LEventBus::instance();

LEventBus & LEventBus::instance()
{
    static LEventBus instance;
    return instance;
}

void LEventBus::subscribe(const QString & event, const LEventBus::Callback & callback)
{
    std::lock_guard<std::mutex> lock(m_mutex); // 锁定互斥锁
    m_callbacks[event].push_back(callback);
}

void LEventBus::publish(const QString & event, const QVariant & var)
{
    QPair<QString, QVariant> pair(event, var);
    m_eventQueue.enqueue(pair);
}

void LEventBus::run()
{
    qDebug() << "事件循环所在线程id:" << QThread::currentThreadId();
    // 执行事件循环
    while (!isInterruptionRequested())
    {
        QPair<QString, QVariant> pair;
        if (m_eventQueue.dequeue(pair))
        {
            std::vector<Callback>       callbacksToExecute;
            std::lock_guard<std::mutex> lock(m_mutex); // 锁定互斥锁
            auto                        it = m_callbacks.find(pair.first);
            if (it != m_callbacks.end())
            {
                callbacksToExecute = it->second;
            }

            for (const auto & callback : callbacksToExecute)
            {
                callback(pair.second);
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
