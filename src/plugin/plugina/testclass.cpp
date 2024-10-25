#include "testclass.h"

#include <list>
#include <memory>
#include <iostream>

// ģ���� EventBus����������¼���ע�ᡢע���Լ��¼��Ĵ���
template <typename EventClass>
class EventBus
{
public:
    // ���캯����ʹ��Ĭ�Ϲ��캯��
    EventBus() = default;

    // ����������ʹ��Ĭ����������
    ~EventBus() = default;

    // ��̬����������ע���¼�
    // ����Ϊ std::weak_ptr ָ����¼����󣬷�ֹѭ������
    static void Register(std::weak_ptr<EventClass> event)
    {
        // ������ע����¼�����ֹ�ظ�ע����ͬ�¼�
        for (std::weak_ptr<EventClass> & registeredEvent : registeredEvents_)
        {
            // ʹ�� weak_ptr �� lock() ��������Ϊ shared_ptr
            std::shared_ptr<EventClass> registeredEventPtr = registeredEvent.lock();
            std::shared_ptr<EventClass> eventPtr           = event.lock();

            // ���ע����¼��ʹ�����¼���ͬ�������־������ע��
            if (registeredEventPtr == eventPtr)
            {
                std::cout << "Skip: event already registered!" << std::endl;
                return;
            }
        }
        // ���¼���ӵ��¼��б���
        registeredEvents_.emplace_back(event);
    }

    // ��̬����������ע���¼�
    // ����Ϊ std::weak_ptr ָ����¼�����
    static void Unregister(std::weak_ptr<EventClass> event)
    {
        // ������ע����¼�
        for (auto eventIt = registeredEvents_.begin(); eventIt != registeredEvents_.end(); ++eventIt)
        {
            // �� weak_ptr ����Ϊ shared_ptr
            std::shared_ptr<EventClass> registeredEventPtr = eventIt->lock();
            std::shared_ptr<EventClass> eventPtr           = event.lock();

            // ����ҵ�ƥ����¼�������б����Ƴ����¼�
            if (registeredEventPtr == eventPtr)
            {
                registeredEvents_.erase(eventIt);
                return;
            }
        }
    }

    // ��̬ģ�巽�������ڴ����¼�
    // ���� fun Ϊ��Ա����ָ�룬args Ϊ�ɱ����
    template <typename EventFunction, typename... EventArgs>
    static void OnEvent(EventFunction eventFunction, EventArgs &&... args)
    {
        // ������ע����¼�
        for (const std::weak_ptr<EventClass> & registeredEvent : registeredEvents_)
        {
            // �� weak_ptr ����Ϊ shared_ptr
            std::shared_ptr<EventClass> eventPtr = registeredEvent.lock();

            // ����¼������ڣ������٣������������־������
            if (!eventPtr)
            {
                std::cerr << "Skip: event no longer exists!" << std::endl;
                continue;
            }

            // ʹ�ó�Ա����ָ�봥���¼��������¼�����ĳ�Ա����
            EventClass * eventObject = eventPtr.get();
            (eventObject->*eventFunction)(std::forward<EventArgs>(args)...);
        }
    }

private:
    // ��̬��Ա�������洢����ע����¼�����ʹ�� weak_ptr �Ա���ѭ�����ã�
    static std::list<std::weak_ptr<EventClass>> registeredEvents_;
};

// ��ʼ����̬��Ա����
template <typename EventClass>
std::list<std::weak_ptr<EventClass>> EventBus<EventClass>::registeredEvents_;

// �ܷ��޸�Ϊ�������ĵ��¼�����,�ӿڲ���Ϊ:
// publish("event_code"��QVariant var);
// int ret = subscribe("event_code"�����ú���(QVariant var)); //retΪ�ص������ÿ���ص�+1�����ظ�
// ���Ĵ��� subscribe ͬʱ��ע�Ṧ�ܣ�
// unsubscribe(ret);ȡ���ص���ȡ��ע�ᣬ��ʵ����





