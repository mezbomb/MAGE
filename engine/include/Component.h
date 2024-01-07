#pragma once
#include "json.hpp"
#include "gfx.h"
#include <glm/glm.hpp>
#include <unordered_map>

namespace MAGE {

    using json = nlohmann::json;

    enum ComponentType {
        BASE,
        TRANSFORM,
        MESH,
        UNKNOWN,
    };

    class Component {
    public:
        ComponentType m_ComponentType;
        unsigned int id;
        virtual void LoadFromJSON(const json& data) = 0;

        Component() : m_ComponentType(ComponentType::BASE), id(0) {}
    };

    class ComponentFactory {
    public:
        typedef std::function<std::shared_ptr<Component>()> ComponentCreator;

        static void RegisterComponentType(const std::string& type_name, ComponentCreator creator) {
            componentCreators[type_name] = creator;
        }

        static std::shared_ptr<Component> CreateComponent(const std::string& type_name) {
            auto it = componentCreators.find(type_name);
            if (it != componentCreators.end()) {
                return it->second();
            }
            return nullptr;
        }

    private:
        static std::unordered_map<std::string, ComponentCreator> componentCreators;
    };

    class ComponentTransform : public Component {
    public:
        ComponentTransform() {
            m_ComponentType = ComponentType::TRANSFORM;
            ComponentFactory::RegisterComponentType("ComponentTransform", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentTransform>(); });
        }

        void LoadFromJSON(const json& data) override {
            if (data.find("position") != data.end()) {
                const json& positionData = data["position"];
                std::vector<float> temp = positionData.get<std::vector<float>>();
                position.x = temp[0];
                position.y = temp[1];
                position.z = temp[2];
            }

            if (data.find("rotation") != data.end()) {
                const json& rotationData = data["rotation"];
                std::vector<float> temp = rotationData.get<std::vector<float>>();
                rotation.x = temp[0];
                rotation.y = temp[1];
                rotation.z = temp[2];
            }

            if (data.find("scale") != data.end()) {
                const json& scaleData = data["scale"];
                std::vector<float> temp = scaleData.get<std::vector<float>>();
                scale.x = temp[0];
                scale.y = temp[1];
                scale.z = temp[2];
            }
        }

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale    = glm::vec3(0.0f);
        glm::vec2 velocity = glm::vec2(0.0f);
    };

    class ComponentMesh : public Component {
    public:
        ComponentMesh() {
            m_ComponentType = ComponentType::MESH;
            ComponentFactory::RegisterComponentType("ComponentMesh", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentMesh>(); });
        }

        void LoadFromJSON(const json& data) override {
            if (data.find("vertices") != data.end()) {
                const json& vertexData = data["vertices"];
                m_verts = vertexData.get<std::vector<float>>();
            }

            if (data.find("program") != data.end()) {
                m_program = data["program"].get<std::string>();
            }
        }
        std::vector<float> m_verts;
        std::string m_program;
    private:
    };

    class ComponentMaterial : public Component {
    public:
        ComponentMaterial() {
            m_ComponentType = ComponentType::UNKNOWN;
            ComponentFactory::RegisterComponentType("ComponentMaterial", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentMaterial>(); });
        }

        void LoadFromJSON(const json& data) override {

        }
    };

    class ComponentAudio : public Component {
    public:
        ComponentAudio() {
            m_ComponentType = ComponentType::UNKNOWN;
            ComponentFactory::RegisterComponentType("ComponentAudio", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentAudio>(); });
        }

        void LoadFromJSON(const json& data) override {

        }
    };

    class ComponentRigidBody : public Component {
    public:
        ComponentRigidBody() {
            m_ComponentType = ComponentType::UNKNOWN;
            ComponentFactory::RegisterComponentType("ComponentRigidBody", []() -> std::shared_ptr<Component> { return std::make_shared<ComponentRigidBody>(); });
        }

        void LoadFromJSON(const json& data) override {

        }
    };
}