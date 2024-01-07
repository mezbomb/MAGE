#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include <unordered_map>

namespace MAGE {
    typedef std::unordered_map<ComponentType, std::shared_ptr<Component>> ComponentMap;

    class Entity {
    public:
        friend class EntityManager;

        ~Entity() { m_Components.clear(); }
        std::string name;
        bool isAlive;

        template<typename T>
        std::shared_ptr<T> GetComponent(ComponentType type) {
            if (m_Components.find(type) != m_Components.end()) {
                return std::dynamic_pointer_cast<T>(m_Components[type]);
            }
            return nullptr;
        }

    private:
        Entity() :
        id(0),
        name("default"),
        isAlive(true) {};

        void AddComponent(std::shared_ptr<Component> component) {
            m_Components[component->m_ComponentType] = component;
        }

        unsigned int id;
        ComponentMap m_Components;
    };

    typedef std::unordered_map<ComponentType, std::vector<std::shared_ptr<Entity>>> EntityComponentMap;
    typedef std::vector<std::shared_ptr<Entity>> EntityContainer;
    typedef std::vector<std::tuple<std::shared_ptr<Entity>, ComponentType>> EntityQueue;
    typedef std::shared_ptr<Entity> EntitySPtr;

    class EntityManager {
    public:
        EntityManager& operator=(const EntityManager&) = delete;
        ~EntityManager() { DestroyAllEntities(); }

        void OnUpdate();

        std::shared_ptr<Entity> CreateEntity();
        EntityContainer& GetAllEntities() { return m_Entities; }
        EntityContainer& GetEntitysByComponent(ComponentType);
        EntitySPtr GetPlayer();

        void AddComponent(std::shared_ptr<Entity>, std::shared_ptr<Component>);
        void DestroyAllEntities();

    private:
        friend class GameEngine;
        EntityManager() {}
        // TODO(mez) write your own allocator scrub :)
        EntityContainer    m_Entities;
        EntityQueue        m_EntityAddQueue;
        EntityComponentMap m_EntityComponentMap;
        EntitySPtr         m_PlayerEntity = nullptr;
        unsigned int       m_EntityCount = 0;

        void QueueEntity(std::tuple<std::shared_ptr<Entity>, ComponentType>);
        void RemoveHandledEntities(EntityContainer&);
    };
}