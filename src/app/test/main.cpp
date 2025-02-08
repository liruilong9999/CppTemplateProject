#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>
#include <luicommon/luicommon.h>
#include <lbase/lbase.h>
#include <QDebug>
#include <lddsbus/lddsbus.h>
#include <QTimer>
#include <queue>

#include "testwidget.h"

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    TestWidget t;
	t.show();

    int ret = a.exec();

    return ret;
}
