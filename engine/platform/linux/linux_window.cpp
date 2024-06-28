#include "linux_window.hpp"
#include "utility/macro.hpp"

Window *Window::create(const WindowProperties &properties) { return new LinuxWindow(properties); }

LinuxWindow::LinuxWindow(const WindowProperties &properties)
{
    m_properties = properties;

    TRACE("window properties size: %i %i pos: %i %i title: %s", m_properties.size.x, m_properties.size.y,
          m_properties.position.x, m_properties.position.y, m_properties.title.c_str());

    m_window = glfwCreateWindow(m_properties.size.x, m_properties.size.y, m_properties.title.c_str(), nullptr, nullptr);

    TRACE("glfw window handle: %p", m_window);

    glfwMakeContextCurrent(m_window);
}

void LinuxWindow::setProperties(const WindowProperties &properties)
{
    TRACE("setting window properties, size: %i %i pos: %i %i title: %s", properties.size.x, properties.size.y,
          properties.position.x, properties.position.y, properties.title.c_str());

    m_properties = properties;
    glfwSetWindowSize(m_window, m_properties.size.x, m_properties.size.y);
    glfwSetWindowPos(m_window, m_properties.position.x, m_properties.position.y);
    glfwSetWindowTitle(m_window, m_properties.title.c_str());
}

void LinuxWindow::update()
{
    glfwGetWindowSize(m_window, &m_properties.size.x, &m_properties.size.y);
    glfwGetWindowPos(m_window, &m_properties.position.x, &m_properties.position.y);
    glfwSwapBuffers(m_window);
}

bool LinuxWindow::shouldClose() const { return glfwWindowShouldClose(m_window); }
