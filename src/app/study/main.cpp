#include <QApplication>
#include <QMenuBar>
#include <lib/pluginmanager/pluginmanager.h>
#include <lib/appskeleton/ipluginview.h>

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "zh_CN.utf8");
    QApplication a(argc, argv);

    // 获取 IPluginView 实例
    AppSkeleton * mainwindow = IPluginView::getInstance().getMainWindow();
    QMenuBar *    menuBar    = mainwindow->menuBar();
    PluginManager::GetInstance().loadAllPlugin();

    IPluginView::getInstance().createMenuBar(menuBar);

    mainwindow->showMaximized();

    int ret = a.exec();
    PluginManager::GetInstance().unloadAllPlugin();

    return ret;
}
