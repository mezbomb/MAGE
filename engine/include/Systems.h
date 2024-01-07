#pragma once
#include "gfx_window.h"
#include <unordered_map>
#include <functional>

namespace MAGE {

    typedef std::unordered_map<int, std::function<void()>> KeyBindMap;

    class System {
        virtual void Run() = 0;
    };

    class InputSystem : public System {
    public:
        InputSystem(GfxWindow* w);
        // Input
        virtual void Run() override;
        void EscapeKeyFn();
        void CloseUIElement();
        void OpenUIElement();
        void PlayerUp();
        void PlayerDown();
        void PlayerLeft();
        void PlayerRight();
        void PlayerShoot();
    private:
        GfxWindow* m_pWindow;
        KeyBindMap m_KeyPressMap;
        KeyBindMap m_KeyReleaseMap;
        std::vector<int> m_Keys;
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