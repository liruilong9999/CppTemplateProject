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

#include "leventbus_global.h"

class LEVENTBUS_EXPORT LEventBus : public QThread
{
    Q_OBJECT
public:
    using Callback = std::function<void(const QVariant &)>;

    static LEventBus & instance();

    void subscribe(const QString & event, const Callback & callback);

    void publish(const QString & event, const QVariant & var);

    void run() override;

private:
    LEventBus();
    ~LEventBus();
    std::map<QString, std::vector<Callback>> m_callbacks;  // 事件-函数列表
    CircularQueue<QPair<QString, QVariant>>  m_eventQueue; // 事件队列
	std::mutex m_mutex;
};

#endif // LEVENTBUS_H