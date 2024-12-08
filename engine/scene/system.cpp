#include "system.hpp"
#include "core/application.hpp"
#include "entt/entt.hpp"
#include "scene/component.hpp"
#include "utility/macro.hpp"

void ComponentSystem::selectScene(Scene &scene)
{
    m_scene = &scene;
}

void ComponentSystem::initialize()
{
    renderer = &Application::get()->renderer;
    Image image;
    image.data = new unsigned char[16];
    image.data[0] = 254;
    image.data[1] = 254;
    image.data[2] = 254;
    image.data[3] = 254;

    image.data[4] = 0;
    image.data[5] = 0;
    image.data[6] = 0;
    image.data[7] = 254;

    image.data[8] = 254;
    image.data[9] = 254;
    image.data[10] = 254;
    image.data[11] = 254;

    image.data[12] = 0;
    image.data[13] = 0;
    image.data[14] = 0;
    image.data[15] = 254;

    image.channels = 4;
    image.size = {2, 2};

    defaultTexture.reset(Texture::create(image));
    delete image.data;
}


void ComponentSystem::drawBoxes()
{
    auto view = m_scene->getView<BoxComponent>();
    for (entt::entity entity : view)
    {
        if (!m_scene->m_registry.all_of<TransformComponent>(entity))
        {
            WARN("entity with [BoxComponent] must also contain [TransformComponent]");
            return;
        }

        TransformComponent &transformComponent = m_scene->m_registry.get<TransformComponent>(entity);
        BoxComponent &boxComponent = m_scene->m_registry.get<BoxComponent>(entity);

        renderer->drawBox(transformComponent.transform, boxComponent.color);
    }
}

void ComponentSystem::drawCircles()
{

    auto view = m_scene->getView<CircleComponent>();
    for (entt::entity entity : view)
    {
        if (!m_scene->m_registry.all_of<TransformComponent>(entity))
        {
            WARN("entity with [CircleComponent] must also contain [TransformComponent]");
            return;
        }

        TransformComponent &transformComponent = m_scene->m_registry.get<TransformComponent>(entity);
        CircleComponent &circleComponent = m_scene->m_registry.get<CircleComponent>(entity);

        renderer->drawCircle(transformComponent.transform, circleComponent.color);
    }
}


void ComponentSystem::drawSprite()
{

    auto view = m_scene->getView<SpriteComponent>();
    for (entt::entity entity : view)
    {
        if (!m_scene->m_registry.all_of<TransformComponent>(entity))
        {
            WARN("entity with [SpriteComponent] must also contain [TransformComponent]");
            return;
        }

        TransformComponent &transformComponent = m_scene->m_registry.get<TransformComponent>(entity);
        SpriteComponent &spriteComponent = m_scene->m_registry.get<SpriteComponent>(entity);

        Sprite sprite;
        sprite.name = spriteComponent.texturePath;
        sprite.count = spriteComponent.spriteCount;
        sprite.index = spriteComponent.spriteIndex;



        if(renderer->hasTexture(sprite.name.c_str()))
        {
            renderer->drawSprite(transformComponent.transform, sprite);
        }

    }
}