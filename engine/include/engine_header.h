#pragma once
#include "engine_systems.h"
#include "gfx.h"
#include "gfx_window.h"
#include <vector>
#include <string>

namespace SAGE {

    enum LAYER_TYPE {
        GAME,
        SCENE,
        RESOURCEMANAGER,
        RENDER,
        DEBUG,
    };

    class Layer {
    public:
        virtual void OnUpdate() = 0;
        LAYER_TYPE m_Type;
    };

    class GameLayer : public Layer {
    public:
        void OnUpdate() override {};
    private:
        InputSystem   m_Input;
        PhysicsSystem m_Physics;
        AudioSystem   m_Audio;
        NetworkSystem m_Net;
    };

    class SceneLayer : public Layer {
    public:
        void OnUpdate() override {};
        // SceneGraph
    };

    class ResourceManagerLayer : public Layer {
    public:
        void OnUpdate() override {};
        // Memory Manager
        // Scheduling Layer
        // -Task Scheduler
        // -JobSystem
    };

    class RenderLayer : public Layer {
    public:
        void OnUpdate() override {};
        // Renderer
    };

    class DebugLayer : public Layer {
    public:
        void OnUpdate() override {};
        // Profiler
        // Output
    };

    struct SAGE_GAME_SETTINGS {
        std::string GameName = "SAGE Game";
        unsigned int WindowWidth = 1280;
        unsigned int WindowHeight = 720;

        SAGE_GAME_SETTINGS(const std::string& name = "SAGE Game", unsigned int w = 1280, unsigned int h = 720)
            : GameName(name), WindowWidth(w), WindowHeight(h) {};
    };

    class GameEngine {
    public:
        GameEngine(const SAGE_GAME_SETTINGS& settings = SAGE_GAME_SETTINGS()) {
            m_Window = gfxCreateWindow(1280, 720, settings.GameName.c_str());
            m_Context = gfxCreateContext(m_Window);
        }
        void UpdateLayers() { for (auto pLayer : m_Layers) { pLayer->OnUpdate(); } }
        void PushLayer(Layer* layer, LAYER_TYPE type) { layer->m_Type = type;  m_Layers.push_back(layer); }
        Layer* GetLayer(LAYER_TYPE type) { for (auto pLayer : m_Layers) { if (pLayer->m_Type == type) return pLayer; } }
    private:
        std::vector<Layer*> m_Layers;
        GfxWindow  m_Window;
        GfxContext m_Context;
    };
}