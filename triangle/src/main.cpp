#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

static void GlfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main(int, char**)
{
    glfwSetErrorCallback(GlfwErrorCallback);
    if(!glfwInit())
    {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, BGFX!", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}