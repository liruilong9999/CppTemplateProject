
#include "levent.h"

LEvent::LEvent(QObject * parent /*= nullptr*/)
{
}

LEvent::~LEvent()
{
}

void LEvent::setObj(void * obj)
{
    m_obj = obj;
}

void LEvent::lEventSlot(Callback & callback, QVariant var, void * obj)
{
    if (obj == m_obj && m_obj != nullptr)
    {
        callback(var);
    }
}
