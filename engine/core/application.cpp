#include "application.hpp"
#include "platform/platform.hpp"
#include "renderer/renderer.hpp"
#include "utility/macro.hpp"
#include <stdio.h>

Application *Application::instance = nullptr;

Application::Application()
{
    if (instance == nullptr)
        instance = this;
    else
        ERROR("only one instance of application is possible");
}
void Application::run()
{
    platformInit();
    WindowProperties windowProperties;
    windowProperties.title = "engine";
    window = Window::create(windowProperties);
    Renderer::init();
    onStart();
    while (!window->shouldClose())
    {
        pollEvent();
        onUpdate();
        window->update();
    }
    onEnd();
    Renderer::terminate();
    platformTerminate();
}
