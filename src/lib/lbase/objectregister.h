#ifndef ObjectRegistry_H__20241109
#define ObjectRegistry_H__20241109

#include <QString>
#include <QMap>
#include <memory>
#include "lcore_global.h"

class LCORE_EXPORT ObjectRegistry
{
public:
    static ObjectRegistry & instance();

    void registerObject(const QString & name, void * object);

    void * getObject(const QString & name) const;

private:
    ObjectRegistry(); // 私有构造函数，单例模式
    QMap<QString, void *> registry;
};

#endif