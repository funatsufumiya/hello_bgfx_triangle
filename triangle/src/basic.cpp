#include <GLFW/glfw3.h>
#include <iostream>
#include <big2.h>
#include <cstdint>
#include <bgfx/platform.h>

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

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, BGFX!", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return 1;
    }

    bgfx::renderFrame();

    bgfx::Init init_object;
    big2::SetNativeWindowData(init_object, window);

    std::int32_t width;
    std::int32_t height;
    glfwGetWindowSize(window, &width, &height);
    init_object.resolution.width = static_cast<uint32_t>(width);
    init_object.resolution.height = static_cast<uint32_t>(height);
    init_object.resolution.reset = BGFX_RESET_VSYNC;

    std::cout << "bgfx::init() ..." << std::endl;

    if (!bgfx::init(init_object))
    {
        return 1;
    }

    std::cout << "bgfx::init() succeeded" << std::endl;

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    // We will use this to reference where we're drawing
    const bgfx::ViewId main_view_id = 0;

    // This is set once to determine the clear color to use on starting a new frame
    bgfx::setViewClear(main_view_id, BGFX_CLEAR_COLOR, 0x000000FF);

    // This is set to determine the size of the drawable surface
    bgfx::setViewRect(main_view_id, 0, 0, static_cast<std::uint16_t>(width), static_cast<std::uint16_t>(height));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Check if window size changed and update the view respectively
        std::int32_t display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        bgfx::reset(display_w, display_h, BGFX_RESET_VSYNC);
        bgfx::setViewRect(main_view_id, 0, 0, bgfx::BackbufferRatio::Equal);

        // Ensure the view is redrawn even if no graphic commands are called
        bgfx::touch(main_view_id);

        // End the frame
        bgfx::frame();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}