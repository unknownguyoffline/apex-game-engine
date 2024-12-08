#include "core/application.hpp"
#include "platform/platform.hpp"
#include "renderer/renderer.hpp"
#include "utility/macro.hpp"
#include "utility/time.hpp"
#include <stdio.h>
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
void Application::run(int argv, char **argc)
{
    argument.argv = argv;
    argument.argc = argc;
    platformInit();

    WindowProperties windowProperties;
    windowProperties.size = {800, 600};
    windowProperties.title = "title";
    windowProperties.position = {20, 20};

    m_window.reset(Window::create(windowProperties));

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("failed to initialize glad");
    }

    renderer.initialize();

    onStart();
    Timer deltaTimer;
    while (m_running)
    {
        pollEvent();
        m_running = !m_window->shouldClose();

        window = m_window->getWindowProperties();
        cursor = m_window->getCursorProperties();
        keyboard = m_window->getKeyboardProperties();
        mouse = m_window->getMouseProperties();

        deltaTimer.start();
        onUpdate(deltaTimer.getDuration());
        layerStack.updateEnabledLayer();
        m_window->update();
        deltaTimer.end();
    }
    onEnd();
    renderer.terminate();
    platformTerminate();
}
