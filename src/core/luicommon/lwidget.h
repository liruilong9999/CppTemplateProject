#ifndef LWIDGET_H
#define LWIDGET_H

#include <QWidget>
#include "luicommon_global.h"

class LUICOMMON_EXPORT LWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LWidget(QWidget * parent = nullptr);
    virtual ~LWidget() override;
};

#endif