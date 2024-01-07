#pragma once
#include "Engine.h"

namespace MAGE {

    class GameLayer : public Layer {
    public:
        GameLayer(GameEngine& g) : 
            m_Parent(g),
            m_InputSystem(g.GetWindow()) { 
            m_Type = LayerType::GAME;
        }
        void OnUpdate() override;
        GameEngine& GetParent() { return m_Parent; }
    private:
        friend class GameEngine;

        GameEngine    m_Parent;

        InputSystem   m_InputSystem;
        PhysicsSystem m_PhysicsSystem;
        AudioSystem   m_AudioSystem;
        // NetworkSystem m_Net; // Single Player :0
    };
}