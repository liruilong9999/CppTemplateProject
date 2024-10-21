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

#include "leventbus_global.h"

class LEVENTBUS_EXPORT LEventBus
{
public:
    //using Data     = QVariant; // 使用 QVariant 作为数据类型
    using Callback = std::function<void(const QVariant &)>;

    static LEventBus & instance();

    void subscribe(const QString & event, const Callback & callback);

    void publish(const QString & event, const QVariant & var);

private:
    LEventBus() = default;
    std::map<QString, std::vector<Callback>> m_callbacks; // 使用 QString 作为事件名
    std::mutex                               m_mutex;     // 用于保护 m_callbacks 的互斥量
};

#endif // LEVENTBUS_H