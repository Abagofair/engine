#pragma once

#include <RGBA.hpp>

#include <stdlib.h>
#include <string>

#include <glad/glad.h>
#include <SDL.h>
#include <SDL_image.h>

#include <glm/glm.hpp>

class Window
{
public:
    Window(
        unsigned short width,
        unsigned short height,
        std::string title);
    ~Window();

    void ClearBuffer(RGBA rgba);
    void SwapBuffers();
    void CenterMouseInWindow();
    glm::uvec2 WindowDimensions();
private:
    Window();
    Window(Window& window);// = delete;

    unsigned short _width;
    unsigned short _height;
    float _aspectRatio;

    SDL_Window* _window;
    SDL_GLContext _context;
};