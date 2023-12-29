#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include <unordered_map>

namespace MAGE {
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

    typedef std::unordered_map<Component::ComponentType, std::vector<std::shared_ptr<Entity>>> EntityComponentMap;
    typedef std::vector<std::shared_ptr<Entity>> EntityContainer;
    typedef std::vector<std::tuple<std::shared_ptr<Entity>, Component::ComponentType>> EntityQueue;

    class EntityManager {
    public:
        EntityManager& operator=(const EntityManager&) = delete;
        ~EntityManager() { DestroyAllEntities(); }

        void OnUpdate();

        std::shared_ptr<Entity> CreateEntity();
        EntityContainer& GetAllEntities() { return m_Entities; }
        EntityContainer& GetEntitysByComponent(Component::ComponentType);

        void AddComponent(std::shared_ptr<Entity>, std::shared_ptr<Component>);
        void DestroyAllEntities();

    private:
        friend class GameEngine;
        EntityManager() {}
        // TODO(mez) write your own allocator scrub :)
        EntityContainer    m_Entities;
        EntityQueue        m_EntityAddQueue;
        EntityComponentMap m_EntityComponentMap;

        void QueueEntity(std::tuple<std::shared_ptr<Entity>, Component::ComponentType>);
        void RemoveHandledEntities(EntityContainer&);
    };
}