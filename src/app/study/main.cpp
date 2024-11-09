#include <QApplication>
#include <QMenuBar>
#include <lib/pluginmanager/pluginmanager.h>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    // 获取 IPluginView 实例
    PluginManager::GetInstance().loadAllPlugin();
    int ret = a.exec();
    PluginManager::GetInstance().unloadAllPlugin();

    return ret;
}
