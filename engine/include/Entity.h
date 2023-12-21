#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include <unordered_map>

namespace SAGE {
    typedef std::unordered_map<Component::ComponentType, std::shared_ptr<Component>> ComponentMap;

    class Entity {
    public:
        friend class EntityManager;

        ~Entity() { m_Components.clear(); }
        unsigned int id;
        std::string name;
        bool isAlive;

        std::shared_ptr<Component> GetComponent(Component::ComponentType type) {
            if (m_Components.find(type) != m_Components.end()) {
                return m_Components[type];
            }
            return nullptr;
        }

    private:
        Entity() :
        id(-1),
        name("default"),
        isAlive(true) {};

        
        void AddComponent(std::shared_ptr<Component> component) {
            m_Components[component->m_ComponentType] = component;
        }


        ComponentMap m_Components;
    };
}