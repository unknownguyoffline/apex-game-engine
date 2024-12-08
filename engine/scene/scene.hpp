#pragma once
#include "entity.hpp"
#include "vendor/entt/entt.hpp"

class Scene
{
  public:
    Entity createEntity();
    Entity getEntity(entt::entity entity);
    void destroyEntity(Entity &entity);

    template <typename T> auto getView()
    {
        return m_registry.view<T>();
    }

    std::vector<std::string> getRequiredTextures();

    void update();

  private:
    friend class ComponentSystem;
    friend class Editor;
    entt::registry m_registry;
};
