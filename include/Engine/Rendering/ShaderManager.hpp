#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <exception>

#include <Engine/Rendering/Shader.hpp>

namespace Engine::Rendering
{
    class ShaderManager
    {
    public:
        ShaderManager();

        uint32_t LoadShader(std::string filePath);
        Shader& GetShader(uint32_t shaderId) const;

    //TODO: Handle deletion
    private:
        std::unordered_map<uint32_t, Shader*> _shadersById;
    };
};