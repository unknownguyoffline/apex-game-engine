#pragma once
#include "core/cursor.hpp"
#include "core/keyboard.hpp"
#include "core/mouse.hpp"
#include "core/window.hpp"
#include <GLFW/glfw3.h>

struct AllProperties
{
    WindowProperties window;
    CursorProperties cursor;
    MouseProperties mouse;
    KeyboardProperties keyboard;
};

class LinuxWindow : public Window
{
  public:
    LinuxWindow(const WindowProperties &properties);
    WindowProperties getWindowProperties() const override;
    CursorProperties getCursorProperties() override;
    MouseProperties getMouseProperties() const override;
    KeyboardProperties getKeyboardProperties() const override;
    void setProperties(const WindowProperties &properties) override;
    void setTitle(const char *title) override;
    void update() override;
    void *getNativeWindow() override;
    bool shouldClose() const override;
    float getAspectRation() const override;

  private:
    GLFWwindow *m_window = nullptr;
    AllProperties m_properties;
};
