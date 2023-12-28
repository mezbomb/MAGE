#pragma once
#include "gfx_window.h"
#include <map>
#include <functional>

namespace MAGE {

    typedef std::map<int, std::function<void()>> KeyBindMap;

    class System {
        virtual void Run() = 0;
    };

    class InputSystem : public System {
    public:
        InputSystem(GfxWindow& w);
        // Input
        virtual void Run() override;
        void Execute(int);
        KeyBindMap* GetKeyBindMap() { return &m_KeyBindings; }
    private:
        friend class GameEngine;

        GfxWindow m_Window;
        KeyBindMap m_KeyBindings;
    };

    class PhysicsSystem : public System {
    public:
        // Physics
        virtual void Run() override {};
    };

    class AudioSystem : public System {
    public:
        // Audio
        virtual void Run() override {};
    };

    class NetworkSystem : public System {
    public:
        // Network
        virtual void Run() override {};
    };
}