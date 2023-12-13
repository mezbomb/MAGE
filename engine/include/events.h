#pragma once

namespace SAGE {

    class Event {
    public:
        enum EventType {
            KEY,
            MOUSE,
        };

        Event(EventType type) : m_Type(type) {}

        EventType GetType() const { return m_Type; }
    private:
        EventType m_Type;
    };
}