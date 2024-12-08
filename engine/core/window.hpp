#pragma once
#include "core/cursor.hpp"
#include "core/keyboard.hpp"
#include "core/mouse.hpp"
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
    virtual WindowProperties getWindowProperties() const = 0;
    virtual CursorProperties getCursorProperties() = 0; // const = 0;
    virtual KeyboardProperties getKeyboardProperties() const = 0;
    virtual MouseProperties getMouseProperties() const = 0;
    virtual void setProperties(const WindowProperties &properties) = 0;
    virtual void setTitle(const char *title) = 0;
    virtual void update() = 0;
    virtual void *getNativeWindow() = 0;
    virtual bool shouldClose() const = 0;
    virtual float getAspectRation() const = 0;
    static Window *create(const WindowProperties &properties);
};
