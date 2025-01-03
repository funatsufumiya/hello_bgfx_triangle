#pragma once
#include <string>
#include <bgfx/bgfx.h>

namespace shader_utils {
    enum class ShaderType {
        Vertex,
        Fragment,
        Compute
    };

    class ShaderLoader {
    public:
        static bgfx::ShaderHandle loadShader(const std::string& name, ShaderType type);
        
    private:
        static std::string getRendererPath();
        static std::vector<uint8_t> loadBinaryFile(const std::string& filepath);
    };
}