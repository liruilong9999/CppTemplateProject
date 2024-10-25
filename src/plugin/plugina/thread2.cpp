
#include <list>
#include <memory>
#include <iostream>
#include <lib/leventbus/leventbus.h>
#include <QThread>
#include <QVariant>
#include <QDebug>
#include "thread2.h"

SubThread2::SubThread2(QObject * parent /*= nullptr*/)
    : QThread(parent)
{
}

SubThread2::~SubThread2()
{
    quit();
    // requestInterruption();
    wait();
}

void SubThread2::run()
{
    qDebug() << "子线程2线程id为：" << QThread::currentThreadId();
    LEventBus::instance().subscribe("test_event", [=](const QVariant & var) {
        qDebug() << "子线程2接收数据，回调线程id为：" << QThread::currentThreadId();
    });

    exec();
}
