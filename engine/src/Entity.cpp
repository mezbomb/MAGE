#include "Entity.h"

namespace MAGE {

    void EntityManager::OnUpdate()
    {
        m_Entities.erase(
            std::remove_if(m_Entities.begin(), m_Entities.end(),
                [](const auto& e) { return !e->isAlive; }),
            m_Entities.end());

        for (auto& tup : m_EntityAddQueue) {
            m_Entities.push_back(std::get<0>(tup));
            m_EntityComponentMap[std::get<1>(tup)].push_back(std::get<0>(tup));
        }
        m_EntityAddQueue.clear();
    }

    std::shared_ptr<Entity> EntityManager::CreateEntity()
    {
        auto entity = std::shared_ptr<Entity>(new Entity());
        QueueEntity(std::make_tuple(entity, Component::ComponentType::BASE));
        return entity;
    }

    void EntityManager::AddComponent(std::shared_ptr<Entity> entity, std::shared_ptr<Component> component)
    {
        entity->AddComponent(component);
        QueueEntity(std::make_tuple(entity, component->m_ComponentType));
    }

    EntityContainer& EntityManager::GetEntitysByComponent(Component::ComponentType type)
    {
        return m_EntityComponentMap[type];
    }

    void EntityManager::DestroyAllEntities()
    {
        m_Entities.clear();
        m_EntityAddQueue.clear();
        m_EntityComponentMap.clear();
    }

    void EntityManager::QueueEntity(std::tuple<std::shared_ptr<Entity>, Component::ComponentType> tuple)
    {
        m_EntityAddQueue.push_back(tuple);
    }
}