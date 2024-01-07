#include "Systems.h"
#include "Events.h"
#include "Engine.h"
#include <iostream>

namespace MAGE {

    InputSystem::InputSystem(GfxWindow* w) :
        m_pWindow(w)
    {
        // TODO(mez) import from JSON
        m_KeyPressMap[VK_UP]     = [this]() { PlayerUp(); };
        m_KeyPressMap[VK_DOWN]   = [this]() { PlayerDown(); };
        m_KeyPressMap[VK_LEFT]   = [this]() { PlayerLeft(); };
        m_KeyPressMap[VK_RIGHT]  = [this]() { PlayerRight(); };
        m_KeyPressMap[VK_SPACE]  = [this]() { PlayerShoot(); };
        m_KeyPressMap[VK_ESCAPE] = [this]() { EscapeKeyFn(); };

        m_KeyReleaseMap[VK_UP]     = []() { };
        m_KeyReleaseMap[VK_DOWN]   = []() { };
        m_KeyReleaseMap[VK_LEFT]   = []() { };
        m_KeyReleaseMap[VK_RIGHT]  = []() { };
        m_KeyReleaseMap[VK_SPACE]  = []() { };
        m_KeyReleaseMap[VK_ESCAPE] = []() { };

        m_Keys = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE, VK_ESCAPE };
    }

    void InputSystem::Run() {
        
        for (auto& key : m_Keys) {
            if (gfxWindowIsKeyPressed(*m_pWindow, key) || gfxWindowIsKeyDown(*m_pWindow, key)) {
                m_KeyPressMap[key]();
            }
            if (gfxWindowIsKeyReleased(*m_pWindow, key)) {
                m_KeyReleaseMap[key]();
            }
        }
    }

    //TODO(mez) move these to somewhere appropriate they will need state like how many ui elements are open.
    void InputSystem::CloseUIElement() { GameEngine::gGameState = GameState::Playing; std::cout << "Playing!\n"; }
    void InputSystem::OpenUIElement() { GameEngine::gGameState = GameState::Menu; std::cout << "Menu!\n"; }

    //This key will not be allowed to be re-bound due to intrinsic handling.
    void InputSystem::EscapeKeyFn() {
        if (GameEngine::gGameState == GameState::Menu) {
            CloseUIElement();
        }
        else  {
            OpenUIElement();
        }
    }

    void InputSystem::PlayerUp() {
        std::cout << "UP\n";
        auto PlayerEntity = GameEngine::m_EntityManager.GetPlayer();
        std::shared_ptr<ComponentTransform> TransformComponent = PlayerEntity->GetComponent<ComponentTransform>(ComponentType::TRANSFORM);
        TransformComponent->position.y += 0.005f;
    }

    void InputSystem::PlayerDown() {
        std::cout << "DOWN\n";
        auto PlayerEntity = GameEngine::m_EntityManager.GetPlayer();
        std::shared_ptr<ComponentTransform> TransformComponent = PlayerEntity->GetComponent<ComponentTransform>(ComponentType::TRANSFORM);
        TransformComponent->position.y -= 0.005f;
    }

    void InputSystem::PlayerLeft() {
        std::cout << "LEFT\n";
        auto PlayerEntity = GameEngine::m_EntityManager.GetPlayer();
        std::shared_ptr<ComponentTransform> TransformComponent = PlayerEntity->GetComponent<ComponentTransform>(ComponentType::TRANSFORM);
        TransformComponent->position.x -= 0.005f;
    }

    void InputSystem::PlayerRight() {
        std::cout << "RIGHT\n";
        auto PlayerEntity = GameEngine::m_EntityManager.GetPlayer();
        std::shared_ptr<ComponentTransform> TransformComponent = PlayerEntity->GetComponent<ComponentTransform>(ComponentType::TRANSFORM);
        TransformComponent->position.x += 0.005f;
    }

    void InputSystem::PlayerShoot() {
        std::cout << "PEW PEW!\n";
    }
}
