#include "linux_window.hpp"
#include "utility/macro.hpp"

Window *Window::create(const WindowProperties &properties)
{
    return new LinuxWindow(properties);
}

LinuxWindow::LinuxWindow(const WindowProperties &properties)
{
    m_properties = properties;
    m_window = glfwCreateWindow(m_properties.size.x, m_properties.size.y, m_properties.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
}

void LinuxWindow::setProperties(const WindowProperties &properties)
{
    m_properties = properties;
    glfwSetWindowSize(m_window, m_properties.size.x, m_properties.size.y);
    glfwSetWindowPos(m_window, m_properties.position.x, m_properties.position.y);
    glfwSetWindowTitle(m_window, m_properties.title.c_str());
}

void LinuxWindow::setTitle(const char *title)
{
    m_properties.title = title;
    glfwSetWindowTitle(m_window, title);
}

void LinuxWindow::update()
{
    glfwGetWindowSize(m_window, &m_properties.size.x, &m_properties.size.y);
    glfwGetWindowPos(m_window, &m_properties.position.x, &m_properties.position.y);
    glfwSwapBuffers(m_window);
}

bool LinuxWindow::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}
