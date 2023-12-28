#pragma once
#include "Engine.h"

namespace MAGE {

    class DebugLayer : public Layer {
    public:
        DebugLayer(GameEngine& g) : m_Parent(g) { m_Type = LayerType::DEBUG; }
        void OnUpdate() override {};

        GameEngine& GetParent() { return m_Parent; }
        // Profiler
        // Output
    private:
        GameEngine m_Parent;
    };
}
