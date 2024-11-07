#ifndef LEVENT_H__20241107
#define LEVENT_H__20241107

#include <QObject>
#include <QVariant>
#include <functional>

#include "leventbus_global.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	暂时考虑适配器模式 + QMetaObject::invokeMethod. </summary>
///				后面大概率用到原型模式
/// <remarks>	Liruilong, 2024/11/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
#define className\
using Callback = void(className::*)(const QVariant &);

class LEVENTBUS_EXPORT LEvent : public QObject
{
    Q_OBJECT
    using Callback = std::function<void(const QVariant &)>;

public:
    LEvent(QObject * parent = nullptr);
    ~LEvent();

    void setObj(void * obj);

signals:

public slots:
    void lEventSlot(Callback & callback, QVariant var, void * obj);

private:
    void * m_obj{nullptr};
};

#define DEF_CLASSSHARED_PTR(className) \
    class className;                   \
    using className##Ptr = std::shared_ptr<className>;

DEF_CLASSSHARED_PTR(LEvent)




#endif
