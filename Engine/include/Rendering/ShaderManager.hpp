#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <exception>

#include "Rendering/Shader.hpp"

namespace Engine::Rendering
{
    class ShaderManager
    {
    public:
        ShaderManager();

        const Shader& LoadShader(std::string filePath, const std::string& name);
        Shader& GetShader(const std::string& name) const;

        static inline std::string const DYNAMIC_SHADER_NAME = "dynamic";
        static inline std::string const STATIC_SHADER_NAME = "static";
        static inline std::string const DEBUG_SHADER_NAME = "debug";

    //TODO: HandleEvents deletion
    private:
        std::unordered_map<std::string, Shader*> _shadersById;
    };
};