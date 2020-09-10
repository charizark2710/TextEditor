#include "glfw3.h"

int Current_WIDTH, Current_HEIGHT;
void GetScreenResolution()
{
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    Current_WIDTH = mode->width;
    Current_HEIGHT = mode->height;
    delete mode;
}