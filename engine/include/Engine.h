#pragma once
// mage
#include "Systems.h"
#include "Events.h"
#include "Entity.h"
// gfx
#include "gfx.h"
#include "gfx_window.h"
#include "gfx_imgui.h"
// std
#include <vector>
#include <string>
#include <queue>
#include <chrono>
#include <Windows.h>

namespace MAGE {

    class Layer {
    public:
        enum LayerType {
            BASE,
            GAME,
            SCENE,
            RESOURCEMANAGER,
            RENDER,
            DEBUG,
            LAYERCOUNT, // always last
        };
        virtual void OnUpdate() = 0;

        LayerType m_Type = LayerType::BASE;

    private:
    };

    struct MAGE_GAME_SETTINGS {
        std::string GameName;
        unsigned int WindowWidth;
        unsigned int WindowHeight;

        MAGE_GAME_SETTINGS(const std::string& name = "MAGE Game", unsigned int w = 1280, unsigned int h = 720)
            : GameName(name), WindowWidth(w), WindowHeight(h) {};
    };

    enum class GameState {
        Playing,
        Paused,
        Menu
    };

    class GameEngine {
    public:
        GameEngine(const MAGE_GAME_SETTINGS& settings = MAGE_GAME_SETTINGS());
        void Run();

        bool GameQuit();

        void* GetParent() { return nullptr; }
        GfxWindow* GetWindow() { return &m_Window; }
        GfxContext* GetContext() { return &m_Context; }

        // Managers
        static EntityManager    m_EntityManager;
        static ComponentFactory m_ComponentManager; //TODO(mez) make factory part of manager use manager type
        static EventManager     m_EventManager;
        // static AssetManager  m_AssetManager;
        static GameState gGameState;

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


    };
}