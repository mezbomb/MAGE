#include "Systems.h"
#include "Events.h"
#include "Engine.h"
#include <iostream>

namespace MAGE {

    InputSystem::InputSystem(GfxWindow& w) : m_Window(w) {
        // TODO(mez) import from JSON
        m_KeyBindings[VK_UP] = []() { /* Player.Move(direction::up) */ };
        m_KeyBindings[VK_DOWN] = []() { /* Player.Move(direction::down) */ };
        m_KeyBindings[VK_LEFT] = []() { /* Player.Move(direction::left) */ };
        m_KeyBindings[VK_RIGHT] = []() { /* Player.Move(direction::right) */ };
        m_KeyBindings[VK_SPACE] = []() { /* Player.Shoot() */ };
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
