#pragma once
#include "engine_systems.h"
#include "gfx.h"
#include "gfx_window.h"
#include <vector>

namespace sage {

    class EngineClass {
    public:
        void engineFunction();
    };

    class Layer {
        std::vector<Layer> m_Layers;
    };

    class GameLayer : public Layer {
        InputSystem   m_Input;
        PhysicsSystem m_Physics;
        AudioSystem   m_Audio;
        NetworkSystem m_Net;
    };

    class SceneLayer : public Layer {
        // SceneGraph
    };

    class ResourceManagerLayer : public Layer {
        // Memory Manager
        // Scheduling Layer
        // -Task Scheduler
        // -JobSystem
    };

    class RenderLayer : public Layer {
        // Renderer
    };

    class DebugLayer : public Layer {
        // Profiler
        // Output
    };
}