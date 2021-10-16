#pragma once

#include <vector>
#include <cstdint>
#include <iostream>
#include <SDL_image.h>

#include "RenderingStructures.hpp"
#include "glPortableHeaders.hpp"

namespace Engine::GLHelper
{
    inline void CreatePosColorTex(uint32_t bufferSize,
                                uint32_t positions,
                                uint32_t colors,
                                uint32_t uvs,
                                uint32_t& vbo,
                                uint32_t& vao,
                                void* data)
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_DYNAMIC_DRAW);

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
        uint32_t componentOffset = ((positions + uvs) * sizeof(float)) + (colors * sizeof(unsigned char));

        //positions / vertex
        glVertexAttribPointer(0, positions, GL_FLOAT, GL_FALSE, componentOffset, (void*)(0));
        glEnableVertexAttribArray(0);
        //color (RGB) / (RGBA) / (BGRA) etc..
        glVertexAttribPointer(1, colors, GL_UNSIGNED_BYTE, GL_TRUE, componentOffset, (void*)(positions * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
        //uv coordinates
        glVertexAttribPointer(2, uvs, GL_FLOAT, GL_FALSE, componentOffset, (void*)((positions * sizeof(GL_FLOAT)) + (colors * sizeof(GL_UNSIGNED_BYTE))));
        glEnableVertexAttribArray(2);

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

    inline void CreateEmptyPosColorTex(uint32_t bufferSize,
                                       uint32_t positions,
                                       uint32_t colors,
                                       uint32_t uvs,
                                       uint32_t& vbo,
                                       uint32_t& vao)
    {
        CreatePosColorTex(
                bufferSize,
                positions,
                colors,
                uvs,
                vbo,
                vao,
                nullptr
        );
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
