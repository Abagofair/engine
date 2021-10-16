#include "RenderInterface.hpp"

namespace Engine::GUI
{
    RenderInterface::RenderInterface(Windowing::Window* window,
        Rendering::ShaderManager& shaderManager,
        glm::mat4 viewMatrix)
        : _window(window), _shaderManager(shaderManager), _viewMatrix(viewMatrix), _bufferElements(20)
    {
        GLHelper::CreateEmptyPosColorTex(
                sizeof(Rml::Vertex) * _bufferElements,
                2,
                4,
                2,
                _vbo,
                _vao);
    }

    void RenderInterface::RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation)
    {
        /* SDL uses shaders that we need to disable here
        glUseProgramObjectARB(0);
        glPushMatrix();

        glTranslatef(translation.x, translation.y, 0);

        Rml::Vector<Rml::Vector2f> Positions(num_vertices);
        Rml::Vector<Rml::Colourb> Colors(num_vertices);
        Rml::Vector<Rml::Vector2f> TexCoords(num_vertices);
        float texw = 0.0f;
        float texh = 0.0f;

        SDL_Texture* sdl_texture = nullptr;
        if(texture)
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            sdl_texture = (SDL_Texture *) texture;
            SDL_GL_BindTexture(sdl_texture, &texw, &texh);
        }

        for(int  i = 0; i < num_vertices; i++)
        {
            Positions[i] = vertices[i].position;
            Colors[i] = vertices[i].colour;
            if (sdl_texture) {
                TexCoords[i].x = vertices[i].tex_coord.x * texw;
                TexCoords[i].y = vertices[i].tex_coord.y * texh;
            }
            else TexCoords[i] = vertices[i].tex_coord;
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &Positions[0]);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, &Colors[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &TexCoords[0]);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        if (sdl_texture) {
            SDL_GL_UnbindTexture(sdl_texture);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glPopMatrix();
        // Reset blending and draw a fake point just outside the screen to let SDL know that it needs to reset its state in case it wants to render a texture
        glDisable(GL_BLEND);
        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_NONE);
        SDL_RenderDrawPoint(mRenderer, -1, -1);*/

        int w, h;
        int miplevel = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);

        //todo: resize texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        for(int  i = 0; i < num_vertices; i++)
        {
            vertices[i].tex_coord.x = vertices[i].tex_coord.x * w;
            vertices[i].tex_coord.x = vertices[i].tex_coord.y * h;
        };
        glBindTexture(GL_TEXTURE_2D, 0);

        auto& shader = _shaderManager.GetShader(Rendering::ShaderManager::DYNAMIC_SHADER_NAME);

        //if (_bufferElements < num_vertices)
        {
            //std::cout << "_bufferElements was too small (" << _bufferElements << ")" << std::endl;
            //std::cout << "resizing to " << num_vertices << std::endl;
            //GLHelper::ResizeVbo(num_vertices, _vbo, vertices);
            //_bufferElements = num_vertices;
            GLHelper::CreatePosColorTex(
                    num_vertices * sizeof(Rml::Vertex),
                    2,
                    4,
                    2,
                    _vbo,
                    _vao,
                    vertices
                    );
        }

        //GLHelper::UpdateVbo<Rml::Vertex>(_vbo, 0, vertices, num_vertices);

        auto tranny = glm::translate(glm::mat4(1.0f),
                                     glm::vec3(translation.x, translation.y, 0.0f));

        shader.Use();
        shader.SetUniformMat4(tranny, "model");
        shader.SetUniformMat4(_viewMatrix, "view");
        GLHelper::DrawVaoWithTexture(_vao, texture, num_vertices, (uint32_t*)indices);
    }

    // Called by RmlUi when it wants to enable or disable scissoring to clip content.
    void RenderInterface::EnableScissorRegion(bool enable)
    {
        if (enable)
            glEnable(GL_SCISSOR_TEST);
        else
            glDisable(GL_SCISSOR_TEST);
    }

    // Called by RmlUi when it wants to change the scissor region.
    void RenderInterface::SetScissorRegion(int x, int y, int width, int height)
    {
        int w_height = _window->WindowDimensions().y;
        glScissor(x, w_height - (y + height), width, height);
    }

    // Called by RmlUi when a texture is required by the library.
    bool RenderInterface::LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source)
    {
        Rml::FileInterface* file_interface = Rml::GetFileInterface();
        Rml::FileHandle file_handle = file_interface->Open(source);
        if (!file_handle)
            return false;

        file_interface->Seek(file_handle, 0, SEEK_END);
        size_t buffer_size = file_interface->Tell(file_handle);
        file_interface->Seek(file_handle, 0, SEEK_SET);

        char* buffer = new char[buffer_size];
        file_interface->Read(buffer, buffer_size, file_handle);
        file_interface->Close(file_handle);

        size_t i;
        for(i = source.length() - 1; i > 0; i--)
        {
            if(source[i] == '.')
                break;
        }

        Rml::String extension = source.substr(i+1, source.length()-i);

        SDL_Surface* surface = IMG_LoadTyped_RW(SDL_RWFromMem(buffer, int(buffer_size)), 1, extension.c_str());

        uint32_t texture;
        GLHelper::Create2DTexture(
                texture,
                surface->w,
                surface->h,
                surface);
        texture_dimensions = Rml::Vector2i(surface->w, surface->h);
        SDL_FreeSurface(surface);

        //todo: don't assume it just works
        return true;
    }

    // Called by RmlUi when a texture is required to be built from an internally-generated sequence of pixels.
    bool RenderInterface::GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions)
    {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 rmask = 0xff000000;
        Uint32 gmask = 0x00ff0000;
        Uint32 bmask = 0x0000ff00;
        Uint32 amask = 0x000000ff;
#else
        Uint32 rmask = 0x000000ff;
        Uint32 gmask = 0x0000ff00;
        Uint32 bmask = 0x00ff0000;
        Uint32 amask = 0xff000000;
#endif

        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom ((void*) source,
                                                         source_dimensions.x,
                                                         source_dimensions.y,
                                                         32,
                                                         source_dimensions.x*4,
                                                         rmask, gmask, bmask, amask);
        uint32_t texture;
        GLHelper::Create2DTexture(
                texture,
                source_dimensions.x,
                source_dimensions.y,
                surface);

        SDL_FreeSurface(surface);
        texture_handle = (Rml::TextureHandle) texture;

        return true;
    }

    // Called by RmlUi when a loaded texture is no longer required.
    void RenderInterface::ReleaseTexture(Rml::TextureHandle texture_handle)
    {
        glDeleteTextures(1, (uint32_t*)texture_handle);
    }
};