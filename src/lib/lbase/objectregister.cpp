#include "objectregister.h"

#include <QDebug>

ObjectRegistry & ObjectRegistry::instance()
{
    static ObjectRegistry instance;
    return instance;
}

void ObjectRegistry::registerObject(const QString & name, void * object)
{
    registry[name] = object;
}

void * ObjectRegistry::getObject(const QString & name) const
{
    auto it = registry.find(name);
    if (it != registry.end())
    {
        return it.value();
    }
    return nullptr;
}

ObjectRegistry::ObjectRegistry()
{
    
}
