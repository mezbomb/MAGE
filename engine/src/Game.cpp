#include "Game.h"

namespace MAGE {
    void GameLayer::OnUpdate() {
        // Game Layer Needs to Execute all the Systems
        m_InputSystem.Run();
        m_PhysicsSystem.Run();
        m_AudioSystem.Run();
    }
}
