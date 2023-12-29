#include "Events.h"
#include <algorithm>

namespace MAGE {

    void EventManager::RemoveHandledEvents(EventContainer& container) {
        container.erase(
            std::remove_if(container.begin(), container.end(),
                [](const auto& e) { return e->isHandled; }),
            container.end());
    }

    void EventManager::OnUpdate()
    {

        RemoveHandledEvents(m_Events);
        for (int i = 0; i < Event::EventType::EVENTCOUNT; i++) {
            RemoveHandledEvents(m_EventTypeMap[static_cast<Event::EventType>(i)]);
        }

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