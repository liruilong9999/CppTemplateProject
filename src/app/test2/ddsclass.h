#ifndef DDSCLASS2_H
#define DDSCLASS2_H

#include <QObject>
#include <lbase/lbase.h>
#include <QDebug>
#include <QVariant>
#include <lddsbus/lddsbus.h>
class DdsClass : public QObject
{
    Q_OBJECT
public:
    DdsClass(QObject * obj = nullptr);
public slots:
    void onSub(const QVariant & var);
};


#endif
