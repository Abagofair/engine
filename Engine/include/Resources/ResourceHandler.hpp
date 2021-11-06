#pragma once

#include <cstdint>
#include <atomic>
#include <unordered_map>
#include <string>

#include <SDL_image.h>

#include "GLHelpers/GlHelper.hpp"

#include "Rendering/Shader.hpp"
#include "Rendering/RenderingStructures.hpp"

namespace Engine::Resources
{
    uint32_t GenerateId();

    const Rendering::Shader& LoadShader(std::string filePath, const std::string& name);
    Rendering::Shader& GetShader(const std::string& name);

    Rendering::Structures::Texture* TextureFromImage(const std::string& filePath);

    static inline std::string const DYNAMIC_SHADER_NAME = "dynamic";
    static inline std::string const STATIC_SHADER_NAME = "static";
    static inline std::string const DEBUG_SHADER_NAME = "debug";
};