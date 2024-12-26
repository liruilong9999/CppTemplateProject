#ifndef LDDSBUS_H__20241225
#define LDDSBUS_H__20241225

#include <QObject>
#include <common/TSingleton.hpp>
#include <QDataStream>
#include <QByteArray>

#include "lcore_global.h"
#include "leventbus.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	The DDS bus. </summary>
///				DDS类，用于分布式通信
///				这个域必须引用方式创建，暂时不支持多个域
/// <remarks>	Liruilong, 2024/12/26. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct LDdsBusPrivate;
class LDdsBus : public TSingleton<LDdsBus>
{
    friend class TSingleton<LDdsBus>;

public:
    LDdsBus();
    ~LDdsBus();

    // 序列化 将 QVariant 转换为 QByteArray
    QByteArray serializeVariant(const QVariant & variant);
    // 反序列化
    // 从 QByteArray 恢复 QVariant
    QVariant deserializeVariant(const QByteArray & byteArray);

    // 创建域
    void createDomain(unsigned int domain = 0);
    // 销毁域
    void destroyDomain(unsigned int domain = 0);

    // 订阅(返回回调存根，根据这个回调存根来取消订阅)
    int subscribeTopic(const QString & event, const char * slotName, QObject * obj);

    // 发布
    void publishTopic(const QString & event, const QVariant & var);

    // 获取查找集，返回所有的数据
    void getFindsetList();

    void unSubscribeTopic(int subStub = 0);

private:
	LDdsBusPrivate * m_pPrivate{nullptr};
};

#endif