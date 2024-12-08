#pragma once
#include "vendor/entt/entt.hpp"
#include "utility/macro.hpp"

class Entity
{
  public:
    template <typename T> T &addComponent();
    template <typename T> void removeComponent();
    template <typename T> T &getComponent();
    template <typename T> bool hasComponent();

    bool operator==(Entity entity)
    {
        entity.m_registry = m_registry;
        return entity.m_entity == m_entity;
    }
    bool isCreated()
    {
        return !(m_registry == nullptr);
    }



  private:
    friend class Scene;
    friend class ComponentSystem;
    entt::entity m_entity;
    entt::registry *m_registry = nullptr;
};

template <typename T> inline T &Entity::addComponent()
{
    return m_registry->emplace<T>(m_entity);
}

template <typename T> inline void Entity::removeComponent()
{
    m_registry->remove<T>(m_entity);
}

template <typename T> inline T &Entity::getComponent()
{
    return m_registry->get<T>(m_entity);
}
template <typename T> inline bool Entity::hasComponent()
{
    if(m_registry == nullptr)
    {
        ERROR("m_registry is null");
    }
    return m_registry->all_of<T>(m_entity);
}
