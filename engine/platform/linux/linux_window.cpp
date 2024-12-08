#include "linux_window.hpp"
#include "utility/macro.hpp"

Window *Window::create(const WindowProperties &properties)
{
    ARG_CHECK(properties.size.x == 0, nullptr);
    ARG_CHECK(properties.size.y == 0, nullptr);
    return new LinuxWindow(properties);
}

void cursorCallback(GLFWwindow *window, double x, double y)
{
    AllProperties *properties = (AllProperties *)glfwGetWindowUserPointer(window);
    glm::dvec2 currentPosition = {x, y};
    properties->cursor.deltaPosition = currentPosition - properties->cursor.position;
    properties->cursor.position = currentPosition;
}
void mouseCallback(GLFWwindow *window, int button, int action, int mod)
{
    AllProperties *properties = (AllProperties *)glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            properties->mouse.leftPressed = true;
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            properties->mouse.rightPressed = true;
    }
    else if (action == GLFW_RELEASE)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            properties->mouse.leftPressed = false;
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            properties->mouse.rightPressed = false;
    }
}
void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mod)
{
    AllProperties *properties = (AllProperties *)glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_SPACE:
            properties->keyboard.space = true;
            break;
        case GLFW_KEY_APOSTROPHE:
            properties->keyboard.apostrophe = true;
            break;
        case GLFW_KEY_COMMA:
            properties->keyboard.comma = true;
            break;
        case GLFW_KEY_MINUS:
            properties->keyboard.minus = true;
            break;
        case GLFW_KEY_PERIOD:
            properties->keyboard.period = true;
            break;
        case GLFW_KEY_SLASH:
            properties->keyboard.slash = true;
            break;
        case GLFW_KEY_0:
            properties->keyboard.number0 = true;
            break;
        case GLFW_KEY_1:
            properties->keyboard.number1 = true;
            break;
        case GLFW_KEY_2:
            properties->keyboard.number2 = true;
            break;
        case GLFW_KEY_3:
            properties->keyboard.number3 = true;
            break;
        case GLFW_KEY_4:
            properties->keyboard.number4 = true;
            break;
        case GLFW_KEY_5:
            properties->keyboard.number5 = true;
            break;
        case GLFW_KEY_6:
            properties->keyboard.number6 = true;
            break;
        case GLFW_KEY_7:
            properties->keyboard.number7 = true;
            break;
        case GLFW_KEY_8:
            properties->keyboard.number8 = true;
            break;
        case GLFW_KEY_9:
            properties->keyboard.number9 = true;
            break;
        case GLFW_KEY_SEMICOLON:
            properties->keyboard.semiColon = true;
            break;
        case GLFW_KEY_EQUAL:
            properties->keyboard.equal = true;
            break;
        case GLFW_KEY_A:
            properties->keyboard.a = true;
            break;
        case GLFW_KEY_B:
            properties->keyboard.b = true;
            break;
        case GLFW_KEY_C:
            properties->keyboard.c = true;
            break;
        case GLFW_KEY_D:
            properties->keyboard.d = true;
            break;
        case GLFW_KEY_E:
            properties->keyboard.e = true;
            break;
        case GLFW_KEY_F:
            properties->keyboard.f = true;
            break;
        case GLFW_KEY_G:
            properties->keyboard.g = true;
            break;
        case GLFW_KEY_H:
            properties->keyboard.h = true;
            break;
        case GLFW_KEY_I:
            properties->keyboard.i = true;
            break;
        case GLFW_KEY_J:
            properties->keyboard.j = true;
            break;
        case GLFW_KEY_K:
            properties->keyboard.k = true;
            break;
        case GLFW_KEY_L:
            properties->keyboard.l = true;
            break;
        case GLFW_KEY_M:
            properties->keyboard.m = true;
            break;
        case GLFW_KEY_N:
            properties->keyboard.n = true;
            break;
        case GLFW_KEY_O:
            properties->keyboard.o = true;
            break;
        case GLFW_KEY_P:
            properties->keyboard.p = true;
            break;
        case GLFW_KEY_Q:
            properties->keyboard.q = true;
            break;
        case GLFW_KEY_R:
            properties->keyboard.r = true;
            break;
        case GLFW_KEY_S:
            properties->keyboard.s = true;
            break;
        case GLFW_KEY_T:
            properties->keyboard.t = true;
            break;
        case GLFW_KEY_U:
            properties->keyboard.u = true;
            break;
        case GLFW_KEY_V:
            properties->keyboard.v = true;
            break;
        case GLFW_KEY_W:
            properties->keyboard.w = true;
            break;
        case GLFW_KEY_X:
            properties->keyboard.x = true;
            break;
        case GLFW_KEY_Y:
            properties->keyboard.y = true;
            break;
        case GLFW_KEY_Z:
            properties->keyboard.z = true;
            break;
        case GLFW_KEY_LEFT_BRACKET:
            properties->keyboard.leftBracket = true;
            break;
        case GLFW_KEY_BACKSLASH:
            properties->keyboard.backSlash = true;
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            properties->keyboard.rightBracket = true;
            break;
        case GLFW_KEY_GRAVE_ACCENT:
            properties->keyboard.graveAccent = true;
            break;
        case GLFW_KEY_WORLD_1:
            properties->keyboard.world1 = true;
            break;
        case GLFW_KEY_WORLD_2:
            properties->keyboard.world2 = true;
            break;

        /* Function keys */
        case GLFW_KEY_ESCAPE:
            properties->keyboard.escape = true;
            break;
        case GLFW_KEY_ENTER:
            properties->keyboard.enter = true;
            break;
        case GLFW_KEY_TAB:
            properties->keyboard.tab = true;
            break;
        case GLFW_KEY_BACKSPACE:
            properties->keyboard.backSpace = true;
            break;
        case GLFW_KEY_INSERT:
            properties->keyboard.insert = true;
            break;
        case GLFW_KEY_DELETE:
            properties->keyboard.del = true;
            break;
        case GLFW_KEY_RIGHT:
            properties->keyboard.right = true;
            break;
        case GLFW_KEY_LEFT:
            properties->keyboard.left = true;
            break;
        case GLFW_KEY_DOWN:
            properties->keyboard.down = true;
            break;
        case GLFW_KEY_UP:
            properties->keyboard.up = true;
            break;
        case GLFW_KEY_PAGE_UP:
            properties->keyboard.pageUp = true;
            break;
        case GLFW_KEY_PAGE_DOWN:
            properties->keyboard.pageDown = true;
            break;
        case GLFW_KEY_HOME:
            properties->keyboard.home = true;
            break;
        case GLFW_KEY_END:
            properties->keyboard.end = true;
            break;
        case GLFW_KEY_CAPS_LOCK:
            properties->keyboard.capsLock = true;
            break;
        case GLFW_KEY_SCROLL_LOCK:
            properties->keyboard.scrollLock = true;
            break;
        case GLFW_KEY_NUM_LOCK:
            properties->keyboard.numLock = true;
            break;
        case GLFW_KEY_PRINT_SCREEN:
            properties->keyboard.printScreen = true;
            break;
        case GLFW_KEY_PAUSE:
            properties->keyboard.pause = true;
            break;
        case GLFW_KEY_F1:
            properties->keyboard.f1 = true;
            break;
        case GLFW_KEY_F2:
            properties->keyboard.f2 = true;
            break;
        case GLFW_KEY_F3:
            properties->keyboard.f3 = true;
            break;
        case GLFW_KEY_F4:
            properties->keyboard.f4 = true;
            break;
        case GLFW_KEY_F5:
            properties->keyboard.f5 = true;
            break;
        case GLFW_KEY_F6:
            properties->keyboard.f6 = true;
            break;
        case GLFW_KEY_F7:
            properties->keyboard.f7 = true;
            break;
        case GLFW_KEY_F8:
            properties->keyboard.f8 = true;
            break;
        case GLFW_KEY_F9:
            properties->keyboard.f9 = true;
            break;
        case GLFW_KEY_F10:
            properties->keyboard.f10 = true;
            break;
        case GLFW_KEY_F11:
            properties->keyboard.f11 = true;
            break;
        case GLFW_KEY_F12:
            properties->keyboard.f12 = true;
            break;
        case GLFW_KEY_F13:
            properties->keyboard.f13 = true;
            break;
        case GLFW_KEY_F14:
            properties->keyboard.f14 = true;
            break;
        case GLFW_KEY_F15:
            properties->keyboard.f15 = true;
            break;
        case GLFW_KEY_F16:
            properties->keyboard.f16 = true;
            break;
        case GLFW_KEY_F17:
            properties->keyboard.f17 = true;
            break;
        case GLFW_KEY_F18:
            properties->keyboard.f18 = true;
            break;
        case GLFW_KEY_F19:
            properties->keyboard.f19 = true;
            break;
        case GLFW_KEY_F20:
            properties->keyboard.f20 = true;
            break;
        case GLFW_KEY_F21:
            properties->keyboard.f21 = true;
            break;
        case GLFW_KEY_F22:
            properties->keyboard.f22 = true;
            break;
        case GLFW_KEY_F23:
            properties->keyboard.f23 = true;
            break;
        case GLFW_KEY_F24:
            properties->keyboard.f24 = true;
            break;
        case GLFW_KEY_F25:
            properties->keyboard.f25 = true;
            break;
        case GLFW_KEY_KP_0:
            properties->keyboard.keypad0 = true;
            break;
        case GLFW_KEY_KP_1:
            properties->keyboard.keypad1 = true;
            break;
        case GLFW_KEY_KP_2:
            properties->keyboard.keypad2 = true;
            break;
        case GLFW_KEY_KP_3:
            properties->keyboard.keypad3 = true;
            break;
        case GLFW_KEY_KP_4:
            properties->keyboard.keypad4 = true;
            break;
        case GLFW_KEY_KP_5:
            properties->keyboard.keypad5 = true;
            break;
        case GLFW_KEY_KP_6:
            properties->keyboard.keypad6 = true;
            break;
        case GLFW_KEY_KP_7:
            properties->keyboard.keypad7 = true;
            break;
        case GLFW_KEY_KP_8:
            properties->keyboard.keypad8 = true;
            break;
        case GLFW_KEY_KP_9:
            properties->keyboard.keypad9 = true;
            break;
        case GLFW_KEY_KP_DECIMAL:
            properties->keyboard.keypadDecimal = true;
            break;
        case GLFW_KEY_KP_DIVIDE:
            properties->keyboard.keypadDivide = true;
            break;
        case GLFW_KEY_KP_MULTIPLY:
            properties->keyboard.keypadMultiply = true;
            break;
        case GLFW_KEY_KP_SUBTRACT:
            properties->keyboard.keypadSubtract = true;
            break;
        case GLFW_KEY_KP_ADD:
            properties->keyboard.keypadAdd = true;
            break;
        case GLFW_KEY_KP_ENTER:
            properties->keyboard.keypadEnter = true;
            break;
        case GLFW_KEY_KP_EQUAL:
            properties->keyboard.keypadEqual = true;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            properties->keyboard.leftShift = true;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            properties->keyboard.leftControl = true;
            break;
        case GLFW_KEY_LEFT_ALT:
            properties->keyboard.leftAlt = true;
            break;
        case GLFW_KEY_LEFT_SUPER:
            properties->keyboard.leftSuper = true;
            break;
        case GLFW_KEY_RIGHT_SHIFT:
            properties->keyboard.rightShift = true;
            break;
        case GLFW_KEY_RIGHT_CONTROL:
            properties->keyboard.rightControl = true;
            break;
        case GLFW_KEY_RIGHT_ALT:
            properties->keyboard.rightAlt = true;
            break;
        case GLFW_KEY_RIGHT_SUPER:
            properties->keyboard.rightSuper = true;
            break;
        case GLFW_KEY_MENU:
            properties->keyboard.menu = true;
            break;
        }
    }

    else if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_SPACE:
            properties->keyboard.space = false;
            break;
        case GLFW_KEY_APOSTROPHE:
            properties->keyboard.apostrophe = false;
            break;
        case GLFW_KEY_COMMA:
            properties->keyboard.comma = false;
            break;
        case GLFW_KEY_MINUS:
            properties->keyboard.minus = false;
            break;
        case GLFW_KEY_PERIOD:
            properties->keyboard.period = false;
            break;
        case GLFW_KEY_SLASH:
            properties->keyboard.slash = false;
            break;
        case GLFW_KEY_0:
            properties->keyboard.number0 = false;
            break;
        case GLFW_KEY_1:
            properties->keyboard.number1 = false;
            break;
        case GLFW_KEY_2:
            properties->keyboard.number2 = false;
            break;
        case GLFW_KEY_3:
            properties->keyboard.number3 = false;
            break;
        case GLFW_KEY_4:
            properties->keyboard.number4 = false;
            break;
        case GLFW_KEY_5:
            properties->keyboard.number5 = false;
            break;
        case GLFW_KEY_6:
            properties->keyboard.number6 = false;
            break;
        case GLFW_KEY_7:
            properties->keyboard.number7 = false;
            break;
        case GLFW_KEY_8:
            properties->keyboard.number8 = false;
            break;
        case GLFW_KEY_9:
            properties->keyboard.number9 = false;
            break;
        case GLFW_KEY_SEMICOLON:
            properties->keyboard.semiColon = false;
            break;
        case GLFW_KEY_EQUAL:
            properties->keyboard.equal = false;
            break;
        case GLFW_KEY_A:
            properties->keyboard.a = false;
            break;
        case GLFW_KEY_B:
            properties->keyboard.b = false;
            break;
        case GLFW_KEY_C:
            properties->keyboard.c = false;
            break;
        case GLFW_KEY_D:
            properties->keyboard.d = false;
            break;
        case GLFW_KEY_E:
            properties->keyboard.e = false;
            break;
        case GLFW_KEY_F:
            properties->keyboard.f = false;
            break;
        case GLFW_KEY_G:
            properties->keyboard.g = false;
            break;
        case GLFW_KEY_H:
            properties->keyboard.h = false;
            break;
        case GLFW_KEY_I:
            properties->keyboard.i = false;
            break;
        case GLFW_KEY_J:
            properties->keyboard.j = false;
            break;
        case GLFW_KEY_K:
            properties->keyboard.k = false;
            break;
        case GLFW_KEY_L:
            properties->keyboard.l = false;
            break;
        case GLFW_KEY_M:
            properties->keyboard.m = false;
            break;
        case GLFW_KEY_N:
            properties->keyboard.n = false;
            break;
        case GLFW_KEY_O:
            properties->keyboard.o = false;
            break;
        case GLFW_KEY_P:
            properties->keyboard.p = false;
            break;
        case GLFW_KEY_Q:
            properties->keyboard.q = false;
            break;
        case GLFW_KEY_R:
            properties->keyboard.r = false;
            break;
        case GLFW_KEY_S:
            properties->keyboard.s = false;
            break;
        case GLFW_KEY_T:
            properties->keyboard.t = false;
            break;
        case GLFW_KEY_U:
            properties->keyboard.u = false;
            break;
        case GLFW_KEY_V:
            properties->keyboard.v = false;
            break;
        case GLFW_KEY_W:
            properties->keyboard.w = false;
            break;
        case GLFW_KEY_X:
            properties->keyboard.x = false;
            break;
        case GLFW_KEY_Y:
            properties->keyboard.y = false;
            break;
        case GLFW_KEY_Z:
            properties->keyboard.z = false;
            break;
        case GLFW_KEY_LEFT_BRACKET:
            properties->keyboard.leftBracket = false;
            break;
        case GLFW_KEY_BACKSLASH:
            properties->keyboard.backSlash = false;
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            properties->keyboard.rightBracket = false;
            break;
        case GLFW_KEY_GRAVE_ACCENT:
            properties->keyboard.graveAccent = false;
            break;
        case GLFW_KEY_WORLD_1:
            properties->keyboard.world1 = false;
            break;
        case GLFW_KEY_WORLD_2:
            properties->keyboard.world2 = false;
            break;

        /* Function keys */
        case GLFW_KEY_ESCAPE:
            properties->keyboard.escape = false;
            break;
        case GLFW_KEY_ENTER:
            properties->keyboard.enter = false;
            break;
        case GLFW_KEY_TAB:
            properties->keyboard.tab = false;
            break;
        case GLFW_KEY_BACKSPACE:
            properties->keyboard.backSpace = false;
            break;
        case GLFW_KEY_INSERT:
            properties->keyboard.insert = false;
            break;
        case GLFW_KEY_DELETE:
            properties->keyboard.del = false;
            break;
        case GLFW_KEY_RIGHT:
            properties->keyboard.right = false;
            break;
        case GLFW_KEY_LEFT:
            properties->keyboard.left = false;
            break;
        case GLFW_KEY_DOWN:
            properties->keyboard.down = false;
            break;
        case GLFW_KEY_UP:
            properties->keyboard.up = false;
            break;
        case GLFW_KEY_PAGE_UP:
            properties->keyboard.pageUp = false;
            break;
        case GLFW_KEY_PAGE_DOWN:
            properties->keyboard.pageDown = false;
            break;
        case GLFW_KEY_HOME:
            properties->keyboard.home = false;
            break;
        case GLFW_KEY_END:
            properties->keyboard.end = false;
            break;
        case GLFW_KEY_CAPS_LOCK:
            properties->keyboard.capsLock = false;
            break;
        case GLFW_KEY_SCROLL_LOCK:
            properties->keyboard.scrollLock = false;
            break;
        case GLFW_KEY_NUM_LOCK:
            properties->keyboard.numLock = false;
            break;
        case GLFW_KEY_PRINT_SCREEN:
            properties->keyboard.printScreen = false;
            break;
        case GLFW_KEY_PAUSE:
            properties->keyboard.pause = false;
            break;
        case GLFW_KEY_F1:
            properties->keyboard.f1 = false;
            break;
        case GLFW_KEY_F2:
            properties->keyboard.f2 = false;
            break;
        case GLFW_KEY_F3:
            properties->keyboard.f3 = false;
            break;
        case GLFW_KEY_F4:
            properties->keyboard.f4 = false;
            break;
        case GLFW_KEY_F5:
            properties->keyboard.f5 = false;
            break;
        case GLFW_KEY_F6:
            properties->keyboard.f6 = false;
            break;
        case GLFW_KEY_F7:
            properties->keyboard.f7 = false;
            break;
        case GLFW_KEY_F8:
            properties->keyboard.f8 = false;
            break;
        case GLFW_KEY_F9:
            properties->keyboard.f9 = false;
            break;
        case GLFW_KEY_F10:
            properties->keyboard.f10 = false;
            break;
        case GLFW_KEY_F11:
            properties->keyboard.f11 = false;
            break;
        case GLFW_KEY_F12:
            properties->keyboard.f12 = false;
            break;
        case GLFW_KEY_F13:
            properties->keyboard.f13 = false;
            break;
        case GLFW_KEY_F14:
            properties->keyboard.f14 = false;
            break;
        case GLFW_KEY_F15:
            properties->keyboard.f15 = false;
            break;
        case GLFW_KEY_F16:
            properties->keyboard.f16 = false;
            break;
        case GLFW_KEY_F17:
            properties->keyboard.f17 = false;
            break;
        case GLFW_KEY_F18:
            properties->keyboard.f18 = false;
            break;
        case GLFW_KEY_F19:
            properties->keyboard.f19 = false;
            break;
        case GLFW_KEY_F20:
            properties->keyboard.f20 = false;
            break;
        case GLFW_KEY_F21:
            properties->keyboard.f21 = false;
            break;
        case GLFW_KEY_F22:
            properties->keyboard.f22 = false;
            break;
        case GLFW_KEY_F23:
            properties->keyboard.f23 = false;
            break;
        case GLFW_KEY_F24:
            properties->keyboard.f24 = false;
            break;
        case GLFW_KEY_F25:
            properties->keyboard.f25 = false;
            break;
        case GLFW_KEY_KP_0:
            properties->keyboard.keypad0 = false;
            break;
        case GLFW_KEY_KP_1:
            properties->keyboard.keypad1 = false;
            break;
        case GLFW_KEY_KP_2:
            properties->keyboard.keypad2 = false;
            break;
        case GLFW_KEY_KP_3:
            properties->keyboard.keypad3 = false;
            break;
        case GLFW_KEY_KP_4:
            properties->keyboard.keypad4 = false;
            break;
        case GLFW_KEY_KP_5:
            properties->keyboard.keypad5 = false;
            break;
        case GLFW_KEY_KP_6:
            properties->keyboard.keypad6 = false;
            break;
        case GLFW_KEY_KP_7:
            properties->keyboard.keypad7 = false;
            break;
        case GLFW_KEY_KP_8:
            properties->keyboard.keypad8 = false;
            break;
        case GLFW_KEY_KP_9:
            properties->keyboard.keypad9 = false;
            break;
        case GLFW_KEY_KP_DECIMAL:
            properties->keyboard.keypadDecimal = false;
            break;
        case GLFW_KEY_KP_DIVIDE:
            properties->keyboard.keypadDivide = false;
            break;
        case GLFW_KEY_KP_MULTIPLY:
            properties->keyboard.keypadMultiply = false;
            break;
        case GLFW_KEY_KP_SUBTRACT:
            properties->keyboard.keypadSubtract = false;
            break;
        case GLFW_KEY_KP_ADD:
            properties->keyboard.keypadAdd = false;
            break;
        case GLFW_KEY_KP_ENTER:
            properties->keyboard.keypadEnter = false;
            break;
        case GLFW_KEY_KP_EQUAL:
            properties->keyboard.keypadEqual = false;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            properties->keyboard.leftShift = false;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            properties->keyboard.leftControl = false;
            break;
        case GLFW_KEY_LEFT_ALT:
            properties->keyboard.leftAlt = false;
            break;
        case GLFW_KEY_LEFT_SUPER:
            properties->keyboard.leftSuper = false;
            break;
        case GLFW_KEY_RIGHT_SHIFT:
            properties->keyboard.rightShift = false;
            break;
        case GLFW_KEY_RIGHT_CONTROL:
            properties->keyboard.rightControl = false;
            break;
        case GLFW_KEY_RIGHT_ALT:
            properties->keyboard.rightAlt = false;
            break;
        case GLFW_KEY_RIGHT_SUPER:
            properties->keyboard.rightSuper = false;
            break;
        case GLFW_KEY_MENU:
            properties->keyboard.menu = false;
            break;
        }
    }
}

LinuxWindow::LinuxWindow(const WindowProperties &properties)
{
    m_properties.window = properties;
    m_window = glfwCreateWindow(m_properties.window.size.x, m_properties.window.size.y, m_properties.window.title.c_str(), nullptr, nullptr);

    ARG_CHECK(m_window == nullptr, );

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_properties);
    glfwSetCursorPosCallback(m_window, cursorCallback);
    glfwSetMouseButtonCallback(m_window, mouseCallback);
    glfwSetKeyCallback(m_window, keyboardCallback);
}

void LinuxWindow::setProperties(const WindowProperties &properties)
{
    m_properties.window = properties;
    glfwSetWindowSize(m_window, m_properties.window.size.x, m_properties.window.size.y);
    glfwSetWindowPos(m_window, m_properties.window.position.x, m_properties.window.position.y);
    glfwSetWindowTitle(m_window, m_properties.window.title.c_str());
}

void LinuxWindow::setTitle(const char *title)
{
    m_properties.window.title = title;
    glfwSetWindowTitle(m_window, title);
}

void LinuxWindow::update()
{
    glfwGetWindowSize(m_window, &m_properties.window.size.x, &m_properties.window.size.y);
    glfwGetWindowPos(m_window, &m_properties.window.position.x, &m_properties.window.position.y);
    glfwSwapBuffers(m_window);
}

bool LinuxWindow::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

float LinuxWindow::getAspectRation() const
{
    return float(m_properties.window.size.x) / float(m_properties.window.size.y);
}

void *LinuxWindow::getNativeWindow()
{
    return m_window;
}

WindowProperties LinuxWindow::getWindowProperties() const
{
    return m_properties.window;
}

CursorProperties LinuxWindow::getCursorProperties()
{
    CursorProperties p = m_properties.cursor;

    m_properties.cursor.deltaPosition = {0, 0};

    // return m_properties.cursor;
    return p;
}

MouseProperties LinuxWindow::getMouseProperties() const
{
    return m_properties.mouse;
}

KeyboardProperties LinuxWindow::getKeyboardProperties() const
{
    return m_properties.keyboard;
}
