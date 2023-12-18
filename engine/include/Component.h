#pragma once
#include "json.hpp"
#include "gfx.h"
#include <unordered_map>

namespace SAGE {

    using json = nlohmann::json;

    class Component {
    public:
        enum ComponentType {
            BASE,
            TRANSFORM,
            MESH,
            UNKNOWN,
        };

        ComponentType m_ComponentType;
        unsigned int id = 0;
        virtual void LoadFromJSON(const json& data) = 0;
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
                position = positionData.get<std::vector<float>>();
            }

            if (data.find("rotation") != data.end()) {
                const json& rotationData = data["rotation"];
                rotation = rotationData.get<std::vector<float>>();
            }

            if (data.find("scale") != data.end()) {
                const json& scaleData = data["scale"];
                scale = scaleData.get<std::vector<float>>();
            }
        }

        std::vector<float> position;
        std::vector<float> rotation;
        std::vector<float> scale;
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