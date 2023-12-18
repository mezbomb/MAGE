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
#include "GameObject.h"

namespace SAGE {

    class Layer {
    public:
        enum LayerType {
            GAME,
            SCENE,
            RESOURCEMANAGER,
            RENDER,
            DEBUG,
            LAYERCOUNT, // always last
        };
        virtual void OnUpdate() = 0;
        virtual std::queue<Event*>& GetEventQueue() = 0;

        LayerType m_Type;

    private:
        //virtual void HandleEvents() = 0;
    };

    class GameLayer : public Layer {
    public:
        GameLayer() { m_Type = LayerType::GAME; }
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
        SceneLayer();
        void OnUpdate() override {};
        virtual void LoadLevel(std::string&);
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
        static std::vector<GameObject*>& GetWorld() { return m_World; }
    private:
        std::queue<Event*> m_EventQueue;
        // SceneGraph
        static std::vector<GameObject*> m_World;
        ComponentFactory m_ComponentFactory;

    };

    class RenderLayer : public Layer {
    public:
        RenderLayer(GfxContext& context) : m_Context(context), m_Time(std::chrono::high_resolution_clock::now()), m_DeltaTime(0.0f) {
            m_Type = LayerType::RENDER;
        }
        void OnUpdate() override;
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
        // Renderer
    private:
        GfxContext& m_Context;
        std::queue<Event*> m_EventQueue;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Time;
        std::chrono::duration<float> m_DeltaTime;
        std::unordered_map<unsigned int, GfxBuffer> m_Buffers;
        std::unordered_map<unsigned int, GfxProgram> m_Programs;
        std::unordered_map<unsigned int, GfxKernel> m_Kernels;
        std::unordered_map<unsigned int, GfxTexture> m_Textures;
    };

    class DebugLayer : public Layer {
    public:
        DebugLayer() { m_Type = LayerType::DEBUG; }
        void OnUpdate() override {};
        virtual std::queue<Event*>& GetEventQueue() override { return m_EventQueue; }
        // Profiler
        // Output
    private:
        std::queue<Event*> m_EventQueue;
    };

    struct SAGE_GAME_SETTINGS {
        std::string GameName;
        unsigned int WindowWidth;
        unsigned int WindowHeight;

        SAGE_GAME_SETTINGS(const std::string& name = "SAGE Game", unsigned int w = 1280, unsigned int h = 720)
            : GameName(name), WindowWidth(w), WindowHeight(h) {};
    };

    class GameEngine {
    public:
        GameEngine(const SAGE_GAME_SETTINGS& settings = SAGE_GAME_SETTINGS());
        void Run();

        bool GameQuit() {
            gfxWindowPumpEvents(m_Window);
            return gfxWindowIsCloseRequested(m_Window) || gfxWindowIsKeyPressed(m_Window, VK_ESCAPE);
        }

    private:
        friend class GameLayer;
        friend class SceneLayer;
        friend class RenderLayer;
        friend class DebugLayer;

        GfxWindow    m_Window;
        GfxContext   m_Context;

        // Layers
        GameLayer*   m_pGameLayer;
        SceneLayer*  m_pSceneLayer;
        RenderLayer* m_pRenderLayer;
        DebugLayer*  m_pDebugLayer;

        // ResourceManager
        // ResourceManager m_ResourceManager;

        // ComponentManager
    };
}