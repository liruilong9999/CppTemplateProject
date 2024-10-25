#include <list>
#include <memory>
#include <iostream>
#include <lib/leventbus/leventbus.h>
#include <QThread>
#include <QVariant>
#include <QDebug>

#include "thread1.h"

SubThread1::SubThread1(QObject * parent /*= nullptr*/)
    : QThread(parent)
{
}

SubThread1::~SubThread1()
{
    quit();
    // requestInterruption();
    wait();
}

void SubThread1::run()
{
	qDebug() << "子线程1线程id为：" << QThread::currentThreadId();
    LEventBus::instance().subscribe("test_event", [=](const QVariant & var) {
        qDebug() << "子线程1接收数据，回调线程id为：" << QThread::currentThreadId();
    });

    exec();
}
