#include "engine_header.h"
#include "events.h"
#include <iostream>
#include "json.hpp"
#include <fstream>
#include "ResourceManager.h"
#include "Component.h"

void SAGE::GameEngine::Run()
{
    m_pGameLayer->OnUpdate();
    m_pSceneLayer->OnUpdate();
    m_pRenderLayer->OnUpdate();
    m_pDebugLayer->OnUpdate();
}

SAGE::GameEngine::GameEngine(const SAGE::SAGE_GAME_SETTINGS& settings)
{
    GfxCreateWindowFlags flags = kGfxCreateWindowFlag_NoResizeWindow;
    m_Window = gfxCreateWindow(settings.WindowWidth, settings.WindowHeight, settings.GameName.c_str(), flags);
    m_Context = gfxCreateContext(m_Window);

    m_pGameLayer   = new SAGE::GameLayer();
    m_pSceneLayer  = new SAGE::SceneLayer();
    m_pRenderLayer = new SAGE::RenderLayer(m_Context);
    m_pDebugLayer  = new SAGE::DebugLayer();

    std::string level = "scene1.json";
    m_pSceneLayer->LoadLevel(level);
}

void SAGE::GameLayer::HandleEvents()
{
    std::queue<Event*> q = GetEventQueue();
    while (!q.empty()) {
        Event* e = q.front();
        q.pop();

        switch (e->GetType()) {
        case Event::EventType::KEY: m_Input.HandleKeyInput(); break;
        default: break;
        }
        //TODO(mez) move to free list and manage event handles to avoid dynamic alloc/dealloc
        delete e;
    }
}

void SAGE::RenderLayer::OnUpdate() {
    auto end = std::chrono::high_resolution_clock::now();
    m_DeltaTime = end - m_Time;
    float time = m_DeltaTime.count();

    float color[] = { 0.5f * cosf(time) + 0.5f,
                        0.5f * sinf(time) + 0.5f,
                        1.0f };

    GfxBuffer vertex_buffer;
    GfxProgram program;
    GfxKernel kernel;

    bool hack = true;
    
    auto world = SAGE::SceneLayer::GetWorld();
    for (auto& obj : world) {
        // only handle mesh for now
        for (auto component : obj->m_components) {
            if (component->m_ComponentType == Component::ComponentType::MESH) {
                auto meshComponent = std::dynamic_pointer_cast<ComponentMesh>(component);
                if (meshComponent) {
                    //create the resources
                    if (hack) {
                        vertex_buffer = gfxCreateBuffer(m_Context, sizeof(float) * meshComponent->m_verts.size(), meshComponent->m_verts.data());
                        m_Buffers[1] = vertex_buffer;
                        program = gfxCreateProgram(m_Context, meshComponent->m_program.c_str());
                        m_Programs[1] = program;
                        kernel = gfxCreateGraphicsKernel(m_Context, program);
                        m_Kernels[1] = kernel;
                        hack = false;
                    }

                    gfxProgramSetParameter(m_Context, m_Programs[1], "Color", color);
                    gfxCommandBindKernel(m_Context, m_Kernels[1]);
                    gfxCommandBindVertexBuffer(m_Context, m_Buffers[1]);
                    gfxCommandDraw(m_Context, 3);
                }
            }
        }
    }


    gfxFrame(m_Context);
}

SAGE::SceneLayer::SceneLayer()
{
    m_Type = LayerType::SCENE;
    ComponentFactory::RegisterComponentType("ComponentTransform", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentTransform>(); });
    ComponentFactory::RegisterComponentType("ComponentMesh", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentMesh>(); });
}

void SAGE::SceneLayer::LoadLevel(std::string& path) {
    using json = nlohmann::json;

    std::ifstream file(path.c_str());
    json data = json::parse(file);

    for (auto& obj : data["gameobjects"]) {
        GameObject* go = new GameObject();
        go->tag = obj["id"];
        for (auto& component : obj["components"]) {
            std::string componentType = component["type"];

            std::shared_ptr<Component> newComponent = m_ComponentFactory.CreateComponent(componentType);
            if (newComponent) {
                newComponent->LoadFromJSON(component);
                go->AddComponent(newComponent);
            }
        }
        m_World.push_back(go);
    }

    file.close();
}
