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
	QPushButton *btn = new QPushButton(this);
	connect(btn,&QPushButton::clicked,[&](){
		/*LDialog dia(this);
		dia.exec();*/
		LFileDialog dia(this);
		QString string = dia.getOpenFileName(this, "Open File", "", "Text Files(*.txt)", nullptr, QFileDialog::Options());
		if (!string.isEmpty())
		{
			QFile file(string);
			if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
			{
				string = file.readAll();
				QStringList strList = string.split("\n");
				for (int i = 0; i < strList.size(); i++) {
					qDebug() << strList[i] << endl;
				}
			}
		}
	});
}

TestWidget::~TestWidget()
{
}
