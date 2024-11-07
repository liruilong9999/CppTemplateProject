#ifndef LEVENTBUS_H
#define LEVENTBUS_H

#include <map>
#include <vector>
#include <functional>
#include <mutex>
#include <thread>
#include <QVariant> // 引入 QVariant
#include <QString>  // 引入 QString
#include <iostream>
#include <common/CircularQueue.h>
#include <QThread>
#include <memory>

#include "leventbus_global.h"
#include "leventbus.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	事件循环类，暂时只支持单线程，多线程情况下是在发布线程执行. </summary>
///
/// <remarks>	Liruilong, 2024/10/25. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class LEVENTBUS_EXPORT LEventBus : public QThread
{
    Q_OBJECT
public:
    using Callback = std::function<void(const QVariant &)>;

    static LEventBus & instance();

    void subscribe(const QString & event, const Callback & callback, void * obj);

    void publish(const QString & event, const QVariant & var);

    void run() override;

    // 注册对象
    void registerObject(void * obj);

    // 注册方法
    void registerMethod(void * obj, Callback & callback);

signals:
    void updateTopicSignal(Callback & callback, QVariant var, void * obj);

private:
    LEventBus();
    ~LEventBus();

	struct CallbackInfo
	{
		Callback callback;
		void * obj;
	};

    std::map<QString, std::vector<CallbackInfo>> m_callbacks;  // 事件类型 -> 回调信息列表
    CircularQueue<QPair<QString, QVariant>>  m_eventQueue; // 事件队列
    std::mutex                               m_mutex;
};

#define EVENT_CLASS_REGISTER(ptr)                     \
    LEventPtr lEventPtr = std::make_shared<LEvent>(); \
    void *    obj       = ptr;                        \
    connect(LEventBus::instance(), &LEventBus::updateTopicSignal, lEvent.get(), &LEvent::lEventSlot, Qt::QueuedConnection);

#endif // LEVENTBUS_H