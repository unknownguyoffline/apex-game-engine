#pragma once
#include "core/layer.hpp"
#include "window.hpp"

class Application
{
  public:
    void run();

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

    Window *window = nullptr;
    LayerStack layerStack;

  private:
    static Application *instance;
};

Application *createApplication();
