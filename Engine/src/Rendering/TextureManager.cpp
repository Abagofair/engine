#include "TextureManager.hpp"

namespace Engine::Rendering
{
    TextureManager::TextureManager(Resources::ResourceHandler& resourceHandler)
        : _resourceHandler(resourceHandler)
    {}

    Rendering::Structures::Texture* TextureManager::TextureFromImage(std::string filePath)
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
        texture->resourceId = _resourceHandler.GenerateId();
        texture->width = static_cast<uint32_t>(image->w);
        texture->height = static_cast<uint32_t>(image->h);

        _texturesById.try_emplace(texture->resourceId, texture);

        SDL_FreeSurface(image);

        return texture;
    }
};