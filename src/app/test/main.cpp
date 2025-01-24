#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>
#include <luicommon/luicommon.h>
#include <lbase/lbase.h>
#include <QDebug>
#include <lddsbus/lddsbus.h>
#include <QTimer>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

	LWidget w;
	w.showMaximized();


    int ret = a.exec();

    return ret;
}
