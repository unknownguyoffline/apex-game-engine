#pragma once
#include "scene/component.hpp"
#include "scene/entity.hpp"
#include "scene/scene.hpp"
#include <memory>

class NativeScript
{
  public:
    virtual void onStart()
    {
    }
    virtual void onUpdate(float dt)
    {
    }
    virtual void onEnd()
    {
    }

    Entity getEntityByName(const char *name)
    {
        auto view = m_scene.getView<EditorPropertyComponent>();
        for (entt::entity e : view)
        {
            Entity entity = m_scene.getEntity(e);
            if (entity.getComponent<EditorPropertyComponent>().name == name)
            {
                return entity;
            }
        }
        WARN("no such entity [%s]", name);
        return {};
    }
    Entity &getEntity()
    {
        return m_entity;
    }
    Scene &getScene()
    {
        return m_scene;
    }
    template <typename T> T &getComponent()
    {
        return m_entity.getComponent<T>();
    }
    template <typename T> void addComponent()
    {
        return m_entity.addComponent<T>();
    }

  private:
    Entity m_entity;
    Scene m_scene;
};

struct NativeScriptComponent
{
    std::shared_ptr<NativeScript> script;
    std::string name;
};
