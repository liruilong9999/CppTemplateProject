#ifndef TESTCLASS2_H
#define TESTCLASS2_H

#include <QObject>
#include <lbase/lbase.h>
#include <lbase/llog.h>

#include <QDebug>

class testClass : public QObject
{
    CLASS_REFLECTION(testClass, "ClassNameStr"); // 仅注册类，不指定模式
    Q_OBJECT
public:
    // ReflectionRegistry * res = ReflectionRegistry::getInstance();
    virtual void print()
    {
        qDebug() << "testClass1";
    };
};

class testClass2 : public testClass
{
    CLASS_REFLECTION(testClass2, "ClassNameStr2"); // 仅注册类，不指定模式
    Q_OBJECT
public:
    // ReflectionRegistry * res = ReflectionRegistry::getInstance();
    void print() override
    {
        qDebug() << "testClass2";
    };
};

#endif
