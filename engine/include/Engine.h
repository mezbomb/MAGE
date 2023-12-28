#pragma once
// mage
#include "Systems.h"
#include "Events.h"
#include "Entity.h"
#include "Scene.h"
// gfx
#include "gfx.h"
#include "gfx_window.h"
#include "gfx_imgui.h"
// std
#include <vector>
#include <string>
#include <queue>
#include <chrono>

namespace MAGE {

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

        LayerType m_Type;

    private:
    };

    class GameLayer : public Layer {
    public:
        GameLayer(GameEngine& g) : m_Parent(g) { m_Type = LayerType::GAME; }
        void OnUpdate() override {};
        GameEngine& GetParent() { return m_Parent; }
    private:
        GameEngine    m_Parent;

        InputSystem   m_Input;
        PhysicsSystem m_Physics;
        AudioSystem   m_Audio;
        // NetworkSystem m_Net; // Single Player :0
    };

    class SceneLayer : public Layer {
    public:
        SceneLayer(GameEngine& g) : m_Parent(g) {};
        void OnUpdate() override;
        virtual void LoadLevel(Scene*);
        virtual void UnloadLevel(Scene*);
        virtual void LoadScenes(std::string&);
        void SwitchScene(std::string& s) { m_CurrentScene = m_Scenes[s]; }
        GameEngine& GetParent() { return m_Parent; }
    private:
        GameEngine& m_Parent;

        Scene* m_CurrentScene;
        std::unordered_map<std::string, Scene*> m_Scenes;
    };

    class RenderLayer : public Layer {
    public:
        RenderLayer(GameEngine& g, GfxContext& c) : m_Parent(g), m_Context(c), m_Time(std::chrono::high_resolution_clock::now()), m_DeltaTime(0.0f) {
            m_Type = LayerType::RENDER;
        }
        void OnUpdate() override;
        GameEngine& GetParent() { return m_Parent; }
        // Renderer
    private:
        GameEngine m_Parent;

        GfxContext m_Context;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Time;
        std::chrono::duration<float> m_DeltaTime;
        std::unordered_map<unsigned int, GfxBuffer>  m_Buffers;
        std::unordered_map<unsigned int, GfxProgram> m_Programs;
        std::unordered_map<unsigned int, GfxKernel>  m_Kernels;
        std::unordered_map<unsigned int, GfxTexture> m_Textures;
    };

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

    struct MAGE_GAME_SETTINGS {
        std::string GameName;
        unsigned int WindowWidth;
        unsigned int WindowHeight;

        MAGE_GAME_SETTINGS(const std::string& name = "MAGE Game", unsigned int w = 1280, unsigned int h = 720)
            : GameName(name), WindowWidth(w), WindowHeight(h) {};
    };

    class GameEngine {
    public:
        GameEngine(const MAGE_GAME_SETTINGS& settings = MAGE_GAME_SETTINGS());
        void Run();

        bool GameQuit() {
            gfxWindowPumpEvents(m_Window);
            return gfxWindowIsCloseRequested(m_Window) || gfxWindowIsKeyPressed(m_Window, VK_ESCAPE);
        }

        void* GetParent() { return nullptr; }

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

        // Managers
        static EntityManager    m_EntityManager;
        static ComponentFactory m_ComponentManager; //TODO(mez) make factory part of manager use manager type
        static EventManager     m_EventManager;
        // static AssetManager  m_AssetManager;
    };
}