#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <exception>

#include <Engine/Rendering/Shader.hpp>

namespace Engine::Rendering
{
    const char * DYNAMIC_SHADER_NAME = "dynamic";
    const char * STATIC_SHADER_NAME = "static";
    const char * DEBUG_SHADER_NAME = "debug";

    class ShaderManager
    {
    public:
        ShaderManager();

        const Shader& LoadShader(std::string filePath, std::string name);
        Shader& GetShader(std::string name) const;

    //TODO: Handle deletion
    private:
        std::unordered_map<std::string, Shader*> _shadersById;
    };
};