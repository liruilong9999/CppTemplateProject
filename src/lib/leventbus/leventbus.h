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
    static LEventBus & instance();

    // 修改为接受 const char* 来传递槽函数名称
    void subscribe(const QString & event, const char* slotName, QObject * obj);

    void publish(const QString & event, const QVariant & var);

    void run() override;

private:
    LEventBus();
    ~LEventBus();

    struct CallbackInfo
    {
        QObject * obj;
        const char* slotName;  // 槽函数名称
    };

    std::map<QString, std::vector<CallbackInfo>> m_callbacks;  // 事件类型 -> 回调信息列表
    CircularQueue<QPair<QString, QVariant>>  m_eventQueue; // 事件队列
    std::mutex                               m_mutex;
};
#endif // LEVENTBUS_H