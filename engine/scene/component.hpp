#pragma once
#include "renderer/types.hpp"
#include "scene/entity.hpp"
#include <string>

struct EditorPropertyComponent
{
    std::string name;
};
struct EntityIdComponent
{
    uint32_t id;
};
struct SpriteComponent
{
    std::string texturePath;
    glm::ivec2 spriteCount = {1, 1};
    glm::ivec2 spriteIndex = {0, 0};
};
struct BoxComponent
{
    glm::vec4 color = glm::vec4(1.f);
};
struct CircleComponent
{
    glm::vec4 color = glm::vec4(1.f);
};
struct TextComponent
{
    std::string text = "No text";
    std::string fontName;
    glm::vec4 color = glm::vec4(1.f);
};
struct TransformComponent
{
    Transform transform;
};

class Script
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

    template <typename T> T &addComponent()
    {
        return entity.addComponent<T>();
    }
    template <typename T> void removeComponent()
    {
        entity.removeComponent<T>();
    }
    template <typename T> T &getComponent()
    {
        return entity.getComponent<T>();
    }

  private:
    friend class ComponentSystem;
    Entity entity;
};

struct ScriptComponent
{
    std::shared_ptr<Script> script;
};