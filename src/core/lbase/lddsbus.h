#ifndef LDDSBUS_H__20241225
#define LDDSBUS_H__20241225

#include <QObject>
#include <common/TSingleton.hpp>
#include <QDataStream>
#include <QByteArray>

#include "lcore_global.h"
#include "leventbus.h"

class LDdsBus : public TSingleton<LDdsBus>
{
    friend class TSingleton<LDdsBus>;

public:
    LDdsBus();
    ~LDdsBus();

	
    // ���л� �� QVariant ת��Ϊ QByteArray
    QByteArray serializeVariant(const QVariant & variant);
	// �����л� 
	// // �� QByteArray �ָ� QVariant
    QVariant deserializeVariant(const QByteArray & byteArray);


    // ������
    void createDomain(unsigned int domain = 0);
    // ������
    void destroyDomain(unsigned int domain = 0);

    // ����(���ػص��������������ص������ȡ������)
    int subscribeTopic(const QString & event, const char * slotName, QObject * obj);

    // ����
    void publishTopic(const QString & event, const QVariant & var);

	// ��ȡ���Ҽ����������е�����
    void getFindsetList();

    void unSubscribeTopic(int subStub = 0);
};

#endif