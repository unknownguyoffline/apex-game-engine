#include "scene.hpp"
#include "component.hpp"

Entity Scene::createEntity()
{
    Entity entity;
    entity.m_entity = m_registry.create();
    entity.m_registry = &m_registry;

    return entity;
}
Entity Scene::getEntity(entt::entity entity)
{
    Entity en;
    en.m_entity = entity;
    en.m_registry = &m_registry;
    return en;
}
void Scene::destroyEntity(Entity &entity)
{
    m_registry.destroy(entity.m_entity);
    entity.m_registry = nullptr;
}

std::vector<std::string> Scene::getRequiredTextures()
{
    std::vector<std::string> requiredTextures;
    auto view = getView<SpriteComponent>();
    for(entt::entity entity : view)
    {
        requiredTextures.push_back(m_registry.get<SpriteComponent>(entity).texturePath);
    }
	return requiredTextures;
}
