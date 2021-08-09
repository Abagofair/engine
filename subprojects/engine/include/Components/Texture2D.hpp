#pragma once

#include <DLLEXPORT.hpp>

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <glPortableHeaders.hpp>

class DLLEXPORT Texture2D
{
public:
    Texture2D(
        std::string path);

    Texture2D(
        unsigned int width,
        unsigned int height);

    ~Texture2D();
    void Bind();
    void Unbind();
    void UpdateTexture(void* pixels);

private:
    Texture2D();
    Texture2D(Texture2D& texture);// = delete;

    unsigned int _glTextureId;
    bool _hasId;
    unsigned short _width;
    unsigned short _height;

    void CopyFromPixels(
        unsigned short width,
        unsigned short height,
        void* pixels);
};