#include "Events.h"
#include <algorithm>

namespace MAGE {

    void EventManager::OnUpdate()
    {
        m_Events.erase(
            std::remove_if(m_Events.begin(), m_Events.end(),
                [](const auto& e) { return e->isHandled; }),
            m_Events.end());

        for (auto& tup : m_EventAddQueue) {
            m_Events.push_back(std::get<0>(tup));
            m_EventTypeMap[std::get<1>(tup)].push_back(std::get<0>(tup));
        }
        m_EventAddQueue.clear();
    }

    std::shared_ptr<Event> EventManager::CreateMageEvent(Event::EventType type, int key)
    {
        auto Event = std::shared_ptr<MAGE::Event>(new MAGE::Event(type, key));
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