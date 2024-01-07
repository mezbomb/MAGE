#include "Scene.h"
#include "json.hpp"

#include <fstream>

namespace MAGE {
    SceneLayer::SceneLayer(GameEngine& g) :
        m_Parent(g),
        m_CurrentScene(new Scene())
    {
        m_Type = LayerType::SCENE;
        m_Scenes[m_CurrentScene->m_Name] = m_CurrentScene;

        ComponentFactory::RegisterComponentType("ComponentTransform", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentTransform>(); });
        ComponentFactory::RegisterComponentType("ComponentMesh", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentMesh>(); });
    }

    void SceneLayer::LoadLevel(Scene* scene) {
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
}