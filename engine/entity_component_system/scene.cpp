#include "scene.hpp"
#include "component.hpp"
#include "entity.hpp"

Entity Scene::createEntity(const std::string &name)
{
    Entity entity(m_registry.create(), m_registry);
    entity.addComponent<Transform>();
    entity.addComponent<EntityInfo>().name = name;
    return entity;
}
void Scene::update() {}
