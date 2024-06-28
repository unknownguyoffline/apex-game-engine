#pragma once
#include "window.hpp"

class Application
{
  public:
    void run();

    virtual void onStart() {}
    virtual void onUpdate() {}
    virtual void onEnd() {}

    static Application *get() { return instance; }

    Application(const Application &) = delete;

    Application();

    Window *window = nullptr;

  private:
    static Application *instance;
};

Application *createApplication();
