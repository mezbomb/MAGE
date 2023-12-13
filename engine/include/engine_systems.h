#pragma once

namespace SAGE {

    class System {
    };

    class InputSystem : public System {
    public:
        // Input
        void HandleKeyInput();
    };

    class PhysicsSystem : public System {
        // Physics
    };

    class AudioSystem : public System {
        // Audio
    };

    class NetworkSystem : public System {
        // Network
    };
}