#pragma once
#include <unordered_map>
#include <vector>
#include <memory>

namespace MAGE {

    class Event {
    public:
        enum EventType {
            ALL,
            INPUT,
            GAME,
            PHYSICS,
            RENDER,
            DEBUG
        };

        Event(EventType type, int id) : m_Type(type), m_EventID(id) {}

        EventType m_Type;
        int m_EventID;
        bool isHandled = false;
    private:
    };

    typedef std::unordered_map<Event::EventType, std::vector<std::shared_ptr<Event>>> EventTypeMap;
    typedef std::vector<std::shared_ptr<Event>> EventContainer;
    typedef std::vector<std::tuple<std::shared_ptr<Event>, Event::EventType>> EventQueue;

    class EventManager {
    public:
        EventManager& operator=(const EventManager&) = delete;
        ~EventManager() { DestroyAllEvents(); }

        void OnUpdate();

        std::shared_ptr<Event> CreateMageEvent(Event::EventType, int);
        EventContainer& GetAllEvents() { return m_Events; }
        EventContainer& GetEventsByType(Event::EventType);
        void DestroyAllEvents();

    private:
        friend class GameEngine;
        EventManager() {}
        // TODO(mez) write your own allocator scrub :)
        EventContainer  m_Events;
        EventQueue      m_EventAddQueue;
        EventTypeMap    m_EventTypeMap;

        void QueueEvent(std::tuple<std::shared_ptr<Event>, Event::EventType>);
    };
}