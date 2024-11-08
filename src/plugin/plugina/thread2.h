#ifndef SubThread2_H
#define SubThread2_H

#include <QThread>
#include <QObject>
#include <lib/leventbus/leventbus.h>
#include <QDebug>

class SubThread2 : public QThread
{
    Q_OBJECT
public:
    SubThread2(QObject * parent = nullptr);
    ~SubThread2();
    void run() override;
};

class TestClass : public QObject
{
    Q_OBJECT
public:
    TestClass(QObject * parent = nullptr)
        : QObject(parent)
    {
       // LEventBus::instance().subscribe("test_event", &TestClass::testSlots, this);
       LEventBus::instance().subscribe("test_event", "testSlots", this);
    }
    ~TestClass(){};

public slots:
   Q_INVOKABLE  void testSlots( int a,int b)
    {
       qDebug() << "testSlots_Ïß³ÌidÎª£º" << QThread::currentThreadId();
       qDebug() << "a£º" << a;
       qDebug() << "b£º" << b;
    }
};


#endif
