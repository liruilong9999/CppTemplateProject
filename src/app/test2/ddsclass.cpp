#include "ddsclass.h"


DdsClass::DdsClass(QObject * obj /*= nullptr*/)
    : QObject(obj)
{
	LDdsBus::instance();
     LEventBus::instance().subscribe("testxxx", SLOT(onSub), this);
}

void DdsClass::onSub(const QVariant & var)
{
     qDebug() << var;
}