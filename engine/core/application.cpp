#include "core/application.hpp"
#include "platform/platform.hpp"
#include "renderer/renderer.hpp"
#include "utility/macro.hpp"
#include "utility/timer.hpp"
#include <stdio.h>
#include <unistd.h>

Application *Application::instance = nullptr;

Application::Application()
{
    if (instance == nullptr)
        instance = this;
    else
    {
        ERROR("only one instance of application is possible");
    }
}
void Application::run()
{
    platformInit();

    WindowProperties windowProperties;
    windowProperties.title = "engine";
    window = Window::create(windowProperties);

    renderer2D.initialize();

    onStart();
    Timer deltaTimer;
    while (!window->shouldClose())
    {
        deltaTimer.start();
        pollEvent();
        onUpdate(deltaTimer.getDuration());
        layerStack.updateEnabledLayer();
        window->update();
        deltaTimer.end();
    }
    onEnd();
    renderer2D.terminate();
    platformTerminate();
}