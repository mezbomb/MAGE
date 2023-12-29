#include "Systems.h"
#include "Events.h"
#include "Engine.h"
#include <iostream>

namespace MAGE {

    InputSystem::InputSystem() {
        // TODO(mez) import from JSON
        m_KeyBindings[VK_UP] = []() { std::cout << "UP\n"; };
        m_KeyBindings[VK_DOWN] = []() { std::cout << "DOWN\n"; };
        m_KeyBindings[VK_LEFT] = []() { std::cout << "LEFT\n"; };
        m_KeyBindings[VK_RIGHT] = []() { std::cout << "RIGHT\n"; };
        m_KeyBindings[VK_SPACE] = []() { std::cout << "PEW PEW!\n"; };
    }

    void InputSystem::Execute(int key) {
        m_KeyBindings[key]();
    }

    void InputSystem::Run() {
        auto& InputEvents = GameEngine::m_EventManager.GetEventsByType(Event::EventType::INPUT);
        for (auto& event : InputEvents) {
            Execute(event->m_EventID);
            event->isHandled = true;
        }
    }
}
