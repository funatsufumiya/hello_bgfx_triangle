#include <GLFW/glfw3.h>
#include <iostream>
#include <big2.h>
#include <cstdint>

#include <big2/bgfx/embedded_shader.h>
#include <generated/shaders/triangle/all.h>

#include <glm/glm.hpp>

struct NormalColorVertex
{
    glm::vec2 position;
    uint32_t color;
};

static const bgfx::EmbeddedShader kEmbeddedShaders[] =
    {
        BGFX_EMBEDDED_SHADER(vs_basic),
        BGFX_EMBEDDED_SHADER(fs_basic),
        BGFX_EMBEDDED_SHADER_END()
    };

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

    bgfx::RendererType::Enum renderer_type = bgfx::getRendererType();
    bgfx::ProgramHandle program = bgfx::createProgram(
            bgfx::createEmbeddedShader(kEmbeddedShaders, renderer_type, "vs_basic"),
            bgfx::createEmbeddedShader(kEmbeddedShaders, renderer_type, "fs_basic"),
            true
    );

    bgfx::VertexLayout color_vertex_layout;
    color_vertex_layout.begin()
                    .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
                    .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
                    .end();

    NormalColorVertex kTriangleVertices[] =
        {
                {{-0.5f, -0.5f}, 0x339933FF},
                {{0.5f, -0.5f}, 0x993333FF},
                {{0.0f, 0.5f}, 0x333399FF},
        };

    const uint16_t kTriangleIndices[] =
            {
                    0, 1, 2,
            };

    // debug log sizeof(kTriangleVertices) and sizeof(kTriangleIndices)
    std::cout << "sizeof(kTriangleVertices): " << sizeof(kTriangleVertices) << std::endl;
    std::cout << "sizeof(kTriangleIndices): " << sizeof(kTriangleIndices) << std::endl;

    bgfx::VertexBufferHandle vertex_buffer = bgfx::createVertexBuffer(bgfx::makeRef(kTriangleVertices, sizeof(kTriangleVertices)), color_vertex_layout);
    bgfx::IndexBufferHandle index_buffer = bgfx::createIndexBuffer(bgfx::makeRef(kTriangleIndices, sizeof(kTriangleIndices)));

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

        bgfx::setState(
            BGFX_STATE_WRITE_R
                    | BGFX_STATE_WRITE_G
                    | BGFX_STATE_WRITE_B
                    | BGFX_STATE_WRITE_A
        );

        bgfx::setVertexBuffer(0, vertex_buffer);
        bgfx::setIndexBuffer(index_buffer); // not needed if you don't do indexed draws
        bgfx::submit(main_view_id, program);

        // End the frame
        bgfx::frame();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}