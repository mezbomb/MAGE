#pragma once
#include "Entity.h"
#include "Component.h"

namespace SAGE {
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
    };
}
