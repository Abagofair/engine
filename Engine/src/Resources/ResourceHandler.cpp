#include "Resources/ResourceHandler.hpp"

namespace Engine::Resources
{
    /*
     * Clang-Tidy: Initialization of '-' with static storage duration may throw an exception that cannot be caught
     * - meaning that if the constructor of the variable throws the exception cannot be caught, because main has not been reached yet.
     */
    namespace
    {
        std::atomic_int _id;
        std::unordered_map<std::string, Rendering::Shader*> _shadersById;
        std::unordered_map<uint32_t, Rendering::Structures::Texture*> _texturesById;
    };

    uint32_t GenerateId()
    {
        return static_cast<uint32_t>(++_id);
    }

    const Rendering::Shader& LoadShader(std::string filePath,
                                                   const std::string& name)
    {
        auto* shader = new Rendering::Shader(std::move(filePath));
        _shadersById.try_emplace(name, shader);
        return *shader;
    }

    Rendering::Shader& GetShader(const std::string& name)
    {
        const auto& iter = _shadersById.find(name);
        if (iter != _shadersById.end())
        {
            return *iter->second;
        }

        throw std::invalid_argument("shader name does not exist");
    }

    Rendering::Structures::Texture* TextureFromImage(const std::string& filePath)
    {
        // load sample.png into image
        SDL_Surface *image;
        image = IMG_Load(filePath.c_str());
        if (!image)
        {
            printf("IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        uint32_t textureHandle;
        GLHelper::Create2DTexture(
                textureHandle,
                image->w,
                image->h,
                image);

        Rendering::Structures::Texture* texture = new Rendering::Structures::Texture();
        texture->filePath = filePath;
        texture->textureHandle = textureHandle;
        texture->resourceId = GenerateId();
        texture->width = static_cast<uint32_t>(image->w);
        texture->height = static_cast<uint32_t>(image->h);

        _texturesById.try_emplace(texture->resourceId, texture);

        SDL_FreeSurface(image);

        return texture;
    }
};