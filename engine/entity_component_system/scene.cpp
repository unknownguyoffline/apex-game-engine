#include "scene.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "utility/macro.hpp"

void Scene::DestroyEntity(Entity &entity)
{
}
Entity Scene::createEntity(const std::string &name)
{
    if (name.size() == 0)
    {
        ERROR("Scene::createEntity name.size = 0");
    }
    Entity entity(m_registry.create(), m_registry);
    entity.addComponent<Transform>().scale = glm::vec3(100, 100, 0);
    entity.addComponent<EntityInfo>().name = name;
    return entity;
}
void Scene::update()
{
}
