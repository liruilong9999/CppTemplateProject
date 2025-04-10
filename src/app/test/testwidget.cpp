#include "testwidget.h"

#include <QPushButton>
#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>
#include <luicommon/luicommon.h>
#include <lbase/lbase.h>
#include <QDebug>
#include <lddsbus/lddsbus.h>
#include <QTimer>
#include <queue>


TestWidget::TestWidget(QWidget * parent /*= nullptr*/)
	:QWidget(parent)
{
	//setFixedSize(200,200);
    setMinimumSize(400, 400);
	QPushButton *btn = new QPushButton(this);
	connect(btn,&QPushButton::clicked,[&](){
		LDialog dia(this);
		dia.exec();
	});
}

TestWidget::~TestWidget()
{
}
