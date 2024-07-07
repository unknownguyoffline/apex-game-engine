#pragma once
#include "core/window.hpp"
#include <vendor/glfw/include/GLFW/glfw3.h>

class LinuxWindow : public Window
{
  public:
    LinuxWindow(const WindowProperties &properties);
    WindowProperties getProperties() const override
    {
        return m_properties;
    }
    void setProperties(const WindowProperties &properties) override;
    void setTitle(const char *title) override;
    void *getNativeWindow() override
    {
        return m_window;
    }
    void update() override;
    bool shouldClose() const override;
    float getAspectRation() const override
    {
        return float(m_properties.size.x) / float(m_properties.size.y);
    }

  private:
    GLFWwindow *m_window = nullptr;
    WindowProperties m_properties;
};
