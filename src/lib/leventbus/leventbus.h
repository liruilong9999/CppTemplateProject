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

struct LEventBusPrivate;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	消息队列类,支持多线程. </summary>
///
/// <remarks>	Liruilong, 2024/10/25. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class LEVENTBUS_EXPORT LEventBus : public QThread
{
    Q_OBJECT
public:
    static LEventBus & instance();

    // 订阅
    void subscribe(const QString & event, const char * slotName, QObject * obj);

    // 发布
    void publish(const QString & event, const QVariant & var);

    void unSubscribe(const QString & event, const char * slotName, QObject * obj);

    void run() override;

private:
    LEventBus();
    ~LEventBus();

    LEventBusPrivate * m_pData{nullptr};
};

#endif // LEVENTBUS_H