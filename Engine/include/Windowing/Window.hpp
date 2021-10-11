#pragma once

#include <stdlib.h>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "External/include/glad/gl.h"
#include "External/include/glm/glm.hpp"

#include "Engine/include/Global/Utilities/RGBA.hpp"

namespace Engine::Windowing
{
    class Window
    {
    public:
        Window(
            unsigned short width,
            unsigned short height,
            std::string title
        );
        Window() = delete;
        Window(Window& window) = delete;
        ~Window();

        void ClearBuffer(Global::Utilities::RGBA rgba);
        void SwapBuffers();
        void CenterMouseInWindow();
        glm::uvec2 WindowDimensions() const;

    private:
        unsigned short _width;
        unsigned short _height;
        float _aspectRatio;

        SDL_Window* _window;
        SDL_GLContext _context;
    };
};