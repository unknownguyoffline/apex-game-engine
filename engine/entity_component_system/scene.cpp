#include "scene.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "utility/macro.hpp"

Entity Scene::createEntity(const std::string &name)
{
    if (name.size() == 0)
    {
        ERROR("Scene::createEntity name.size = 0");
    }
    Entity entity(m_registry.create(), m_registry);
    entity.addComponent<Transform>();
    entity.addComponent<EntityInfo>().name = name;
    return entity;
}
void Scene::update()
{
}
