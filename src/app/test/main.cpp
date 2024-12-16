#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>
#include <luicommon/luicommon.h>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

	LTitleBar bar;
	bar.setTitle("测试标题");
	bar.show();


    int ret = a.exec();

    return ret;
}
