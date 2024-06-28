#pragma once
#include <glm/glm.hpp>
#include <string>

struct WindowProperties
{
    std::string title = "Untitled";
    glm::ivec2 size = glm::ivec2(800, 600);
    glm::ivec2 position = glm::ivec2(0);
};

class Window
{
  public:
    virtual WindowProperties getProperties() const = 0;
    virtual void setProperties(const WindowProperties &properties) = 0;
    virtual void update() = 0;
    virtual void *getNativeWindow() = 0;
    virtual bool shouldClose() const = 0;
    static Window *create(const WindowProperties &properties);
};
