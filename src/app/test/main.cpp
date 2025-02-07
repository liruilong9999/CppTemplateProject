#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>
#include <luicommon/luicommon.h>
#include <lbase/lbase.h>
#include <QDebug>
#include <lddsbus/lddsbus.h>
#include <QTimer>
#include <queue>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    LDialog w;
    w.setWindowTitle("Test");
    w.showNormal();

    int ret = a.exec();

    return ret;
}
