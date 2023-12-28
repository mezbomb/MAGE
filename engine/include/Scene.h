#pragma once
#include "Engine.h"
#include "Entity.h"

#include <vector>
#include <string>

namespace MAGE {

    class Scene {
    public:
        Scene() : m_Name("empty"), m_Extension(""), m_Path("") {}
        Scene(std::string n, std::string e, std::string p) :
            m_Name(n),
            m_Extension(e),
            m_Path(p) {}

        bool m_Loaded = false;

        std::string m_Name;
        std::string m_Extension;
        std::string m_Path;
        std::vector<std::shared_ptr<Entity>> m_Entities;
    };

    class SceneLayer : public Layer {
    public:
        SceneLayer(GameEngine& g);
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
}