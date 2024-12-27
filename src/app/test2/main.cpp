#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>
#include <luicommon/luicommon.h>
#include <lbase/lbase.h>
#include <QDebug>

#include "ddsclass.h"

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

	DdsClass class1;


    int ret = a.exec();

    return ret;
}
