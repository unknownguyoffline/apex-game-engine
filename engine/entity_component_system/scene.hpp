#pragma once
#include "entity.hpp"
#include "renderer/texture_library.hpp"
#include <string>
#include <vector>
#include <vendor/entt/entt.hpp>

class Scene
{
  public:
    Entity createEntity(const std::string &name);
    template <typename T> std::vector<Entity> getList()
    {
        std::vector<Entity> list;
        auto view = m_registry.view<T>();
        for (entt::entity entity : view)
        {
            list.push_back(Entity(entity, m_registry));
        }
        return list;
    }
    void DestroyEntity(Entity &entity);
    void update();
    TextureLibrary textureLibrary;

  private:
    entt::registry m_registry;
    friend Entity;
};
