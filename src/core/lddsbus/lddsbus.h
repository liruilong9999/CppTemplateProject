#ifndef LDDSBUS_H__20241225
#define LDDSBUS_H__20241225

#include <QObject>
#include <common/TSingleton.hpp>
#include <QDataStream>
#include <QByteArray>

#include <QThread>
#include <mutex>
#include <shared_mutex> // 引入共享锁头文件

#include "ldds_global.h"

enum DisplayModelState
{
    RunningState = 0, // 推演模式
    PlayBackState     // 回放模式
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	The DDS bus. </summary>
///				DDS类，用于分布式通信
///				这个域必须引用方式创建，暂时不支持多个域
/// <remarks>	Liruilong, 2024/12/26. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct LDdsBusPrivate;
class LDDSBUS_EXPORT LDdsBus :  public QThread
{
	Q_OBJECT
public:
    LDdsBus();
    ~LDdsBus();
	static LDdsBus & instance();

    // 序列化 将 QVariant 转换为 QByteArray
    QByteArray serializeVariant(const QVariant & variant);
    // 反序列化
    // 从 QByteArray 恢复 QVariant
    QVariant deserializeVariant(const QByteArray & byteArray);

    // 订阅(返回回调存根，根据这个回调存根来取消订阅)
    int subscribeTopic( QString  event,  char * slotName, QObject * obj);

    // 发布
    void publishTopic( QString event,  QVariant  var);

    // 获取查找集，返回所有的数据
    void getFindsetList();

    void unSubscribeTopic(int subStub = 0);


	DisplayModelState getDisplayModelState();
	void setDisplayModelState(DisplayModelState model = DisplayModelState::RunningState);

protected:
	void run() override;

private:
    LDdsBusPrivate * m_pPrivate{nullptr};
	DisplayModelState m_displaySate{DisplayModelState::RunningState};
	std::mutex m_mutex; // 互斥锁，用于保护共享资源
	 std::shared_mutex m_sharedMutex; // 共享锁
};

#endif