#include "Engine.h"
#include "Events.h"
#include <iostream>
#include "json.hpp"
#include <fstream>
#include "Events.h"
#include "Component.h"

namespace MAGE {
    EntityManager GameEngine::m_EntityManager;
    EventManager GameEngine::m_EventManager;
    ComponentFactory GameEngine::m_ComponentManager;
    //AssetManager GameEngine::m_AssetManager;
}

void MAGE::GameEngine::Run()
{
    m_EventManager.OnUpdate();
    m_EntityManager.OnUpdate();
    m_pGameLayer->OnUpdate();
    m_pSceneLayer->OnUpdate();
    m_pRenderLayer->OnUpdate();
    m_pDebugLayer->OnUpdate();
}

MAGE::GameEngine::GameEngine(const MAGE::MAGE_GAME_SETTINGS& settings)
{
    GfxCreateWindowFlags flags = kGfxCreateWindowFlag_NoResizeWindow;
    m_Window = gfxCreateWindow(settings.WindowWidth, settings.WindowHeight, settings.GameName.c_str(), flags);
    //TODO(mez) make this a preprocessor macro
    m_Context = gfxCreateContext(m_Window, kGfxCreateContextFlag_EnableDebugLayer);

    m_pGameLayer   = new MAGE::GameLayer();
    m_pSceneLayer  = new MAGE::SceneLayer();
    m_pRenderLayer = new MAGE::RenderLayer(m_Context);
    m_pDebugLayer  = new MAGE::DebugLayer();

    std::string level = "scene1.json";
    m_pSceneLayer->LoadScenes(level);
}

void MAGE::RenderLayer::OnUpdate() {
    auto end = std::chrono::high_resolution_clock::now();
    m_DeltaTime = end - m_Time;
    float time = m_DeltaTime.count();

    float color[] = { 0.5f * cosf(time) + 0.5f,
                        0.5f * sinf(time) + 0.5f,
                        1.0f };

    GfxBuffer vertex_buffer;
    GfxProgram program;
    GfxKernel kernel;
    
    auto mesh_entities = GameEngine::m_EntityManager.GetEntitysByComponent(Component::ComponentType::MESH);
    for (auto entity : mesh_entities) {
        auto meshComponent = std::dynamic_pointer_cast<ComponentMesh>(entity->GetComponent(Component::ComponentType::MESH));
        if (meshComponent) {
            //create the resources
            if (m_Buffers.empty()) {
                vertex_buffer = gfxCreateBuffer(m_Context, sizeof(float) * meshComponent->m_verts.size(), meshComponent->m_verts.data());
                m_Buffers[1] = vertex_buffer;
                program = gfxCreateProgram(m_Context, meshComponent->m_program.c_str());
                m_Programs[1] = program;
                kernel = gfxCreateGraphicsKernel(m_Context, program);
                m_Kernels[1] = kernel;
            }
            
            gfxProgramSetParameter(m_Context, m_Programs[1], "Color", color);
            gfxCommandBindKernel(m_Context, m_Kernels[1]);
            gfxCommandBindVertexBuffer(m_Context, m_Buffers[1]);
            gfxCommandDraw(m_Context, 3);
        }
    }
    gfxFrame(m_Context);
}

MAGE::SceneLayer::SceneLayer()
{
    m_Type = LayerType::SCENE;
    m_CurrentScene = new Scene();
    m_Scenes[m_CurrentScene->m_Name] = m_CurrentScene;

    ComponentFactory::RegisterComponentType("ComponentTransform", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentTransform>(); });
    ComponentFactory::RegisterComponentType("ComponentMesh", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentMesh>(); });
}

void MAGE::SceneLayer::LoadLevel(Scene* scene) {
    if (false == scene->m_Loaded)
    {
        using json = nlohmann::json;
        std::string fullpath = scene->m_Path + scene->m_Name + scene->m_Extension;
        std::ifstream file(fullpath.c_str());
        json data = json::parse(file);

        for (auto s : data["scenes"]) {
            if (s["name"] == scene->m_Name) {
                for (auto& e : s["entities"]) {
                    auto entity = GameEngine::m_EntityManager.CreateEntity();
                    entity->id = e["id"];
                    entity->isAlive = e["isAlive"];
                    entity->name = e["name"];

                    for (auto& component : e["components"]) {
                        std::string componentType = component["type"];

                        std::shared_ptr<Component> newComponent = GameEngine::m_ComponentManager.CreateComponent(componentType);
                        if (newComponent) {
                            newComponent->LoadFromJSON(component);
                            GameEngine::m_EntityManager.AddComponent(entity, newComponent);
                        }
                    }
                    scene->m_Entities.push_back(entity);
                }
            }
        }

        file.close();
        scene->m_Loaded = true;
    }
}

void MAGE::SceneLayer::UnloadLevel(Scene* s)
{
    //TODO(mez) make sure all entities are marked unalive so EntityManager cleans them up.
    s->m_Entities.clear();
}

void MAGE::SceneLayer::OnUpdate() {
    // Think about how to handle this.
    // Check event manager for LoadLevel Event
    // Parse the message (level name)
    // Load the level..
    // if no level specified or its invalid load an empty scene.

    // for now pretend we got a load level event:
    std::string sceneName = "scene1";
    if (m_CurrentScene && m_CurrentScene->m_Name != sceneName) {
        if (m_Scenes.find(sceneName) != m_Scenes.end()) {
            if (m_Scenes[sceneName]->m_Loaded)
                SwitchScene(sceneName);
            else {
                LoadLevel(m_Scenes[sceneName]); //TODO(mez) this function should probably have success condition returned.
                SwitchScene(sceneName);
            }
        }
        else {
            SwitchScene(std::string("empty"));
        }
    }
}

void MAGE::SceneLayer::LoadScenes(std::string& path) {
    using json = nlohmann::json;

    std::ifstream file(path.c_str());
    json data = json::parse(file);

    for (auto& scene : data["scenes"]) {
        Scene* s = new Scene(
            scene["name"],
            scene["extension"],
            scene["path"]);
        m_Scenes[s->m_Name] = s;
    }

    file.close();
}