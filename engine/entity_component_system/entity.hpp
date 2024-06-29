#pragma once
#include "utility/macro.hpp"
#include <vendor/entt/entt.hpp>

class Editor;

class Entity
{
  public:
    Entity()
    {
    }
    Entity(entt::entity entity, entt::registry &registry) : m_entity(entity), m_registry(&registry)
    {
    }
    Entity(const Entity &entity) : m_entity(entity.m_entity), m_registry(entity.m_registry)
    {
    }

    template <typename T> T &addComponent()
    {
        m_registry->emplace<T>(m_entity);
        return m_registry->get<T>(m_entity);
    }
    template <typename T> bool hasComponent()
    {
        if (m_registry == nullptr)
        {
            ERROR("Entity::hasComponent [m_registry = nullptr]");
        }
        return m_registry->all_of<T>(m_entity);
    }
    template <typename T> T &getComponent()
    {
        return m_registry->get<T>(m_entity);
    }
    template <typename T> T getComponent() const
    {
        return m_registry->get<T>(m_entity);
    }
    void operator=(const Entity &entity)
    {
        m_entity = entity.m_entity;
        m_registry = entity.m_registry;
    }

  private:
    friend Editor;
    entt::entity m_entity;
    entt::registry *m_registry = nullptr;
};
