#pragma once

#include <vector>
#include <cstdint>
#include <iostream>
#include <SDL_image.h>

#include "Rendering/RenderingStructures.hpp"
#include "Global/glPortableHeaders.hpp"

#include <RmlUi/Core.h>

namespace Engine::GLHelper
{
    inline void CreateRmlBuffers(
            uint32_t& vbo,
            uint32_t& vao,
            Rml::Vertex* vertices,
            uint32_t vertexCount)
    {
        if (vbo > 0)
            glDeleteBuffers(1, &vbo);
        if (vao > 0)
            glDeleteBuffers(1, &vao);

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Rml::Vertex) * vertexCount, &vertices[0], GL_DYNAMIC_DRAW);

        /* glVertexAttribPointer(
         * INDEX,
         * COMPONENTS PER ATTRIBUTE,
         * DATA TYPE OF EACH COMPONENT,
         * SHOULD NORMALIZE VALUES,
         * POINTER TO DATA TO COPY INTO BUFFER,
         * STRIDE BETWEEN ATTRIBUTES - 0 IS TIGHTLY PACKED
         * OFFSET FOR EACH ATTRIBUTE RELATIVE TO FIRST COMPONENT
         * *
         */
        //positions / vertex
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Rml::Vertex), (void*)(0));
        //color (RGB) / (RGBA) / (BGRA) etc..
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Rml::Vertex), (void*) offsetof(Rml::Vertex, colour));
        //uv coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Rml::Vertex), (void*) offsetof(Rml::Vertex, tex_coord));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    inline void VboVaoEboPosColorTex(std::array<Rendering::Structures::Vertex, 4> vertices,
                                  uint32_t indexSize,
                                  uint32_t* indices,
                                  uint32_t positions,
                                  uint32_t colors,
                                  uint32_t uvs,
                                  uint32_t& vbo,
                                  uint32_t& vao,
                                  uint32_t& ebo)
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Rendering::Structures::Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, &indices[0], GL_DYNAMIC_DRAW);

        /* glVertexAttribPointer(
         * INDEX,
         * COMPONENTS PER ATTRIBUTE,
         * DATA TYPE OF EACH COMPONENT,
         * SHOULD NORMALIZE VALUES,
         * POINTER TO DATA TO COPY INTO BUFFER,
         * STRIDE BETWEEN ATTRIBUTES - 0 IS TIGHTLY PACKED
         * OFFSET FOR EACH ATTRIBUTE RELATIVE TO FIRST COMPONENT
         * *
         */
        //positions / vertex
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, positions, GL_FLOAT, GL_FALSE, sizeof(Rendering::Structures::Vertex), (void*)(0));
        //color (RGB) / (RGBA) / (BGRA) etc..
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, colors, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Rendering::Structures::Vertex), (void*) offsetof(Rendering::Structures::Vertex, color));
        //uv coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, uvs, GL_FLOAT, GL_FALSE, sizeof(Rendering::Structures::Vertex), (void*) offsetof(Rendering::Structures::Vertex, uv));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    inline void ResizeVbo(uint32_t newSize, uint32_t vbo, void* data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, newSize, data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    template<typename T>
    inline void UpdateVbo(uint32_t vbo, uint32_t offset, const T* vertices, uint32_t count)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(T), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    inline void DrawVaoWithTexture(uint32_t vao, uint32_t texture, uint32_t count, uint32_t* indices)
    {
        if (texture > 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            
        }

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, indices);
        glBindVertexArray(0);
    }

    inline void Create2DTexture(uint32_t& texture, uint32_t width, uint32_t height, SDL_Surface* surface)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
};
