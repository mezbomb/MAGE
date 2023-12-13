#pragma once
#include "engine_systems.h"
#include "gfx.h"
#include "gfx_window.h"
#include <vector>
#include <string>
#include "gfx_imgui.h"
#include <queue>
#include "events.h"
#include <chrono>

namespace SAGE {

    class GameObject {
    public:
        unsigned int tag;
    };

    class Layer {
    public:
        enum LayerType {
            GAME,
            SCENE,
            RESOURCEMANAGER,
            RENDER,
            DEBUG,
        };
        virtual void OnUpdate() = 0;
        virtual std::queue<Event*>& GetEventQueue() = 0;

        LayerType m_Type;

    private:
        //virtual void HandleEvents() = 0;
    };

    class GameLayer : public Layer {
    public:
        void OnUpdate() override { HandleEvents(); };
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
    private:
        void HandleEvents();
        std::queue<Event*> m_EventQueue;
        InputSystem   m_Input;
        PhysicsSystem m_Physics;
        AudioSystem   m_Audio;
        NetworkSystem m_Net;
    };

    class SceneLayer : public Layer {
    public:
        void OnUpdate() override {};
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
        // SceneGraph
    private:
        std::queue<Event*> m_EventQueue;
        std::vector<GameObject> m_World;
    };

    class ResourceManagerLayer : public Layer {
    public:
        void OnUpdate() override {};
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
        // Memory Manager
        // Scheduling Layer
        // -Task Scheduler
        // -JobSystem
    private:
        std::queue<Event*> m_EventQueue;
    };

    class RenderLayer : public Layer {
    public:
        RenderLayer(GfxContext& context) : m_Context(context), m_Time(std::chrono::high_resolution_clock::now()), m_DeltaTime(0.0f) {
            vertices[0] = 0.5f;
            vertices[1] = -0.5f;
            vertices[2] = 0.0f;
            vertices[3] = 0.0f;
            vertices[4] = 0.7f;
            vertices[5] = 0.0f;
            vertices[6] = -0.5f;
            vertices[7] = -0.5f;
            vertices[8] = 0.0f;

            vertex_buffer = gfxCreateBuffer(m_Context, sizeof(vertices), vertices);
            program = gfxCreateProgram(m_Context, "triangle");
            kernel = gfxCreateGraphicsKernel(m_Context, program);
        }
        void OnUpdate() override;
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
        // Renderer

        //TODO(mez) hacking this for now trying to get a triangle up
        float vertices[9];
        GfxBuffer vertex_buffer;
        GfxProgram program;
        GfxKernel kernel;
    private:
        std::queue<Event*> m_EventQueue;
        GfxContext& m_Context;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Time;
        std::chrono::duration<float> m_DeltaTime;
    };

    class DebugLayer : public Layer {
    public:
        void OnUpdate() override {};
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
        // Profiler
        // Output
    private:
        std::queue<Event*> m_EventQueue;
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
            GfxCreateWindowFlags flags = kGfxCreateWindowFlag_NoResizeWindow;
            m_Window = gfxCreateWindow(1280, 720, settings.GameName.c_str(), flags);
            m_Context = gfxCreateContext(m_Window);
        }
        void UpdateLayers() { for (auto layer : m_Layers) { layer->OnUpdate(); } }
        void PushLayer(Layer* layer, Layer::LayerType type) { layer->m_Type = type;  m_Layers.push_back(layer); }
        Layer* GetLayer(Layer::LayerType type) { for (auto layer : m_Layers) { if (layer->m_Type == type) return layer; } }
        GfxContext& GetContext() { return m_Context; }

        bool GameQuit() {
            gfxWindowPumpEvents(m_Window);
            return gfxWindowIsCloseRequested(m_Window) || gfxWindowIsKeyPressed(m_Window, VK_ESCAPE);
        }

    private:
        std::vector<Layer*> m_Layers;
        GfxWindow  m_Window;
        GfxContext m_Context;
    };
}