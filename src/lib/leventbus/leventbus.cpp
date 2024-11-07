#include <QDebug>
#include "leventbus.h"

// 全局变量，确保在 main 函数执行之前初始化
// LEventBus & globalEventBus = LEventBus::instance();

LEventBus & LEventBus::instance()
{
    static LEventBus instance;
    return instance;
}

void LEventBus::subscribe(const QString & event, const Callback & callback, void * obj)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_callbacks[event].push_back({callback, obj});
}

void LEventBus::publish(const QString & event, const QVariant & var)
{
    m_eventQueue.enqueue(qMakePair(event, var));
}

void LEventBus::run()
{
    // 执行事件循环
    while (!isInterruptionRequested())
    {
        QPair<QString, QVariant> eventPair;
        if (m_eventQueue.dequeue(eventPair))
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            auto                        it = m_callbacks.find(eventPair.first);

            std::vector<CallbackInfo> callbacksToExecute;
            if (it != m_callbacks.end())
            {
                callbacksToExecute = it->second;
                for (CallbackInfo callback : callbacksToExecute)
                {
                    emit updateTopicSignal(callback.callback, eventPair.first, callback.obj);
                }
            }
        }
    }
}

void LEventBus::registerObject(void * obj)
{
}

void LEventBus::registerMethod(void * obj, Callback & callback)
{
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
