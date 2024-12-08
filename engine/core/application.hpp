#pragma once
#include "core/cursor.hpp"
#include "core/keyboard.hpp"
#include "core/layer.hpp"
#include "core/mouse.hpp"
#include "renderer/renderer.hpp"
#include "window.hpp"

struct Argument
{
    int argv = 0;
    char **argc;
};
class Application
{
  public:
    void run(int argv, char **argc);

    virtual void onStart()
    {
    }
    virtual void onUpdate(float dt)
    {
    }
    virtual void onEnd()
    {
    }

    static Application *get()
    {
        return instance;
    }
    Application(const Application &) = delete;
    Application();

    LayerStack layerStack;
    Renderer renderer;

    WindowProperties window;
    CursorProperties cursor;
    KeyboardProperties keyboard;
    MouseProperties mouse;

    Argument argument;

    std::shared_ptr<Window> getWindow()
    {
        return m_window;
    }

  private:
    bool m_running = true;
    static Application *instance;
    std::shared_ptr<Window> m_window;
};

Application *createApplication();
