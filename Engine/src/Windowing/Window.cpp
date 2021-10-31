#include "Windowing/Window.hpp"

namespace Engine::Windowing
{
    Window::Window(
        unsigned short width,
        unsigned short height,
        std::string title,
        const Global::Utilities::Logger &logger)
            : _width(width), _height(height), _logger(logger)
    {
        _logger.WriteInfo("Initializing window..", "");
        _logger.WriteInfo("Width: %, Height: %", width, height);

        //https://bcmpinc.wordpress.com/2015/08/18/creating-an-opengl-4-5-context-using-sdl2-and-glad/
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
        IMG_Init(IMG_INIT_PNG);

        SDL_GL_LoadLibrary(NULL);

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        //As stated earlier in the post, we want to sync rendering to our monitor’s refresh rate. This is done using SDL_GL_SetSwapInterval.
        // Use v-sync
        SDL_GL_SetSwapInterval(1);

        _aspectRatio = (float)width / (float)height;

        _window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, 
            height,
            SDL_WINDOW_OPENGL
        );

        _context = SDL_GL_CreateContext(_window);

        // Check OpenGL properties
        //printf("OpenGL loaded\n");

        _logger.WriteInfo("OpenGL loaded", "");

        gladLoaderLoadGL();
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        _logger.WriteInfo("Vendor:   %", glGetString(GL_VENDOR));
        _logger.WriteInfo("Renderer: %", glGetString(GL_RENDERER));
        _logger.WriteInfo("Version:  %", glGetString(GL_VERSION));
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(_context);
        SDL_DestroyWindow(_window);
    }

    void Window::ClearBuffer(Global::Utilities::RGBA rgba)
    {
        glClearColor(rgba.RgbaVec.x, rgba.RgbaVec.y, rgba.RgbaVec.z, rgba.RgbaVec.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::SwapBuffers()
    {
        SDL_GL_SwapWindow(_window);
    }

    void Window::CenterMouseInWindow()
    {
        SDL_WarpMouseInWindow(_window, _width / 2, _height / 2);
    }

    glm::uvec2 Window::WindowDimensions() const
    {
        return glm::uvec2(_width, _height);
    }
};