#include "reflection.h"

QObject * ClassFactory::getClassByName(const QString & className, ObjectCreationMode mode)
{
    if (mode == ObjectCreationMode::Singleton)
    {
        // ����ģʽ������Ƿ����ж���
        if (!m_singletonsMap.contains(className))
        {
            // ���û�У��������������
            auto createFunc = m_classMap.value(className);
            if (createFunc)
            {
                m_singletonsMap[className] = createFunc();
            }
        }
        return m_singletonsMap.value(className, nullptr); // ���û�У��򷵻� nullptr
    }
    else
    {
        // ԭ��ģʽ��ÿ�δ����¶���
        auto createFunc = m_classMap.value(className);
        if (createFunc)
        {
            return createFunc();
        }
    }
    return nullptr; // ���û���ҵ���Ӧ�Ĵ������������� nullptr
}

void ClassFactory::registClass(const QString & name, PTRCreateObject method)
{
    m_classMap.insert(name, method);
}

ClassFactory & ClassFactory::getInstance()
{
    static ClassFactory sLo_factory;
    return sLo_factory;
}

RegisterAction::RegisterAction(const QString & className, PTRCreateObject ptrCreateFn)
{
    ClassFactory::getInstance().registClass(className, ptrCreateFn);
}