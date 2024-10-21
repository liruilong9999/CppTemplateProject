#include "leventbus.h"

LEventBus & LEventBus::instance()
{
    static LEventBus instance;
    return instance;
}

void LEventBus::subscribe(const QString & event, const LEventBus::Callback & callback)
{
    std::lock_guard<std::mutex> lock(m_mutex); // 使用互斥量保护共享资源
    m_callbacks[event].push_back(callback);
}

void LEventBus::publish(const QString & event, const QVariant & var)
{
    std::vector<Callback> callbacksToExecute;

    {
        std::lock_guard<std::mutex> lock(m_mutex); // 保护对 m_callbacks 的访问
        auto                        it = m_callbacks.find(event);
        if (it != m_callbacks.end())
        {
            callbacksToExecute = it->second;
        }
    }

    // 在各自线程中执行回调函数
    for (const auto & callback : callbacksToExecute)
    {
        std::thread([callback, var]() {
            callback(var);
        }).detach(); // 创建线程并立即分离
    }
}
