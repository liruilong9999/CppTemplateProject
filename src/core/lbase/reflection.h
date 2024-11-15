#ifndef REFLECTION_H__20241114
#define REFLECTION_H__20241114

#include "lcore_global.h"

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>
#include <core/common/TSingleton.hpp>

// 定义单例模式和原型模式
enum class ObjectMode
{
    Singleton, // 单例模式
    Prototype  // 原型模式
};

class ReflectionRegistry : public TSingleton<ReflectionRegistry>
{
    friend class TSingleton<ReflectionRegistry>;

public:
    // 注册类工厂，不指定模式，而是提供创建设备的函数
    void registerClass(const QString & className, QObject * (*creator)())
    {
        qDebug() << classRegistry.size();
        classRegistry[className] = {creator};
        qDebug() << classRegistry.size();
    }

    // 获取对象，单例模式下返回同一个对象，原型模式下每次返回新对象
    QObject * getObject(const QString & className, ObjectMode mode = ObjectMode::Prototype)
    {
        auto it = classRegistry.find(className);
        if (it != classRegistry.end())
        {
            if (mode == ObjectMode::Singleton)
            {
                if (!singletonInstances.contains(className))
                {
                    singletonInstances[className] = it.value().creator(); // 创建并缓存单例
                }
                return singletonInstances[className]; // 返回单例对象
            }
            else
            {
                return it.value().creator(); // 每次创建新对象（原型模式）
            }
        }
        return nullptr; // 如果没有找到对应的类
    }

private:
    // 存储类创建函数
    struct ClassInfo
    {
        QObject * (*creator)(); // 类的创建函数
    };

    QMap<QString, ClassInfo> classRegistry;      // 类注册表
    QMap<QString, QObject *> singletonInstances; // 存储单例对象（使用普通指针）
};

#define CLASS_REFLECTION(ClassName, String)                                       \
    friend class ReflectionRegistry;                                              \
    static QObject * createInstance()                                             \
    {                                                                             \
        return new ClassName();                                                   \
    }                                                                             \
    bool _classReflectionRegistered_##ClassName = []() {                          \
        ReflectionRegistry::getInstance()->registerClass(String, createInstance); \
        return true;                                                              \
    }();
#endif
