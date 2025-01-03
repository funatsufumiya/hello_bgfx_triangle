#include "shader_loader.hpp"
#include <fstream>
#include <stdexcept>

namespace shader_utils {

std::string ShaderLoader::getRendererPath() {
    const auto renderer = bgfx::getRendererType();
    
    switch (renderer) {
        case bgfx::RendererType::Direct3D11:
        case bgfx::RendererType::Direct3D12:
            return "dx11/";
            
        case bgfx::RendererType::OpenGL:
            return "glsl/";
            
        case bgfx::RendererType::Metal:
            return "metal/";
            
        case bgfx::RendererType::Vulkan:
            return "spirv/";
            
        default:
            throw std::runtime_error("Unsupported renderer: " + 
                std::string(bgfx::getRendererName(renderer)));
    }
}

std::vector<uint8_t> ShaderLoader::loadBinaryFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + filepath);
    }

    const auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<uint8_t> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    
    return buffer;
}

bgfx::ShaderHandle ShaderLoader::loadShader(const std::string& name, ShaderType type) {
    const std::string base_path = "triangle/res/shaders/";
    const std::string renderer_path = getRendererPath();
    const std::string type_prefix = (type == ShaderType::Vertex) ? "vs_" : (type == ShaderType::Fragment) ? "fs_" : "cs_";
    
    const std::string full_path = base_path + renderer_path + type_prefix + name + ".bin";
    
    auto shader_data = loadBinaryFile(full_path);
    const bgfx::Memory* mem = bgfx::copy(shader_data.data(), shader_data.size());
    
    return bgfx::createShader(mem);
}

}