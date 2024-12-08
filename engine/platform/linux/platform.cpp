#include "platform/platform.hpp"
#include <GLFW/glfw3.h>

void platformInit() { glfwInit(); }
void platformTerminate() { glfwTerminate(); }
void pollEvent() { glfwPollEvents(); }
