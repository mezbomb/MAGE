#include "Engine.h"
#include "Game.h"
#include "Render.h"
#include "Debug.h"
#include "Scene.h"

namespace MAGE {

    EntityManager GameEngine::m_EntityManager;
    EventManager GameEngine::m_EventManager;
    ComponentFactory GameEngine::m_ComponentManager;
    //AssetManager GameEngine::m_AssetManager;

    void GameEngine::Run()
    {
        m_EventManager.OnUpdate();
        m_EntityManager.OnUpdate();
        m_pGameLayer->OnUpdate();
        m_pSceneLayer->OnUpdate();
        m_pRenderLayer->OnUpdate();
        m_pDebugLayer->OnUpdate();
    }

    bool GameEngine::GameQuit() {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
            if (msg.message == WM_KEYDOWN) {
                int key = static_cast<int>(msg.wParam);
                auto keyBindings = m_pGameLayer->m_InputSystem.GetKeyBindMap();
                if (keyBindings->find(key) != keyBindings->end()) {
                    m_EventManager.CreateMageEvent(Event::EventType::INPUT, key);
                }
            }
            GetMessage(&msg, nullptr, 0, 0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        gfxWindowPumpEvents(m_Window);
        return gfxWindowIsCloseRequested(m_Window);
    }

    GameEngine::GameEngine(const MAGE::MAGE_GAME_SETTINGS& settings)
    {
        GfxCreateWindowFlags flags = kGfxCreateWindowFlag_NoResizeWindow;
        m_Window = gfxCreateWindow(settings.WindowWidth, settings.WindowHeight, settings.GameName.c_str(), flags);
        //TODO(mez) make this a preprocessor macro
        m_Context = gfxCreateContext(m_Window, kGfxCreateContextFlag_EnableDebugLayer);

        m_pGameLayer = new MAGE::GameLayer(*this);
        m_pSceneLayer = new MAGE::SceneLayer(*this);
        m_pRenderLayer = new MAGE::RenderLayer(*this, m_Context);
        m_pDebugLayer = new MAGE::DebugLayer(*this);

        std::string level = "scene1.json";
        m_pSceneLayer->LoadScenes(level);
    }
}



