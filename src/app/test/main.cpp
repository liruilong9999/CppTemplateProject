#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>
#include <luicommon/luicommon.h>
#include <lbase/appconfig.h>
#include <QDebug>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    QString mark = "root.st1.data";
    QString mark2 = "root.str2.data";
    QString name = "namexxx";
    QString data = "dataxxx";
    AppConfig::getInstance()->setAppConfig(mark2, "data6666666");

    QString res1 = AppConfig::getInstance()->getAppConfig(mark, name);
    QString res2 = AppConfig::getInstance()->getAppConfig(mark2, name);

    qDebug() << res1;
    qDebug() << res2;

    int ret = a.exec();

    return ret;
}
