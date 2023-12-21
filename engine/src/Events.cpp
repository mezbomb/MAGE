#include "Events.h"

namespace MAGE {

    void EventManager::OnUpdate()
    {
        //TODO(mez) 100% should unit test this.
        for (auto e : m_Events) {
            while (e->isHandled) {
                std::swap(e, m_Events.back());
                m_Events.pop_back();
            }
        }
        for (auto& tup : m_EventAddQueue) {
            m_Events.push_back(std::get<0>(tup));
            m_EventTypeMap[std::get<1>(tup)].push_back(std::get<0>(tup));
        }
        m_EventAddQueue.clear();
    }

    std::shared_ptr<Event> EventManager::CreateMageEvent(Event::EventType type)
    {
        auto Event = std::shared_ptr<MAGE::Event>(new MAGE::Event(type));
        QueueEvent(std::make_tuple(Event, type));
        return Event;
    }

    EventContainer& EventManager::GetEventsByType(Event::EventType type)
    {
        return m_EventTypeMap[type];
    }

    void EventManager::DestroyAllEvents()
    {
        m_Events.clear();
        m_EventAddQueue.clear();
        m_EventTypeMap.clear();
    }

    void EventManager::QueueEvent(std::tuple<std::shared_ptr<Event>, Event::EventType> tuple)
    {
        m_EventAddQueue.push_back(tuple);
    }
}