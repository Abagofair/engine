#pragma once

#include <cstdint>

#include <vector>

#include <glm/glm.hpp>

#include <glPortableHeaders.hpp>

float quadVertices[12] = 
{
    -0.05f,  0.05f,  0.0f,
    0.05f, -0.05f,  0.0f,
    -0.05f, -0.05f,  0.0f,
    0.05f,  0.05f,  0.0f
};

float quadIndices[6] =
{
    2, 0, 3,
    3, 1, 2
};

struct Renderable
{
    uint32_t vbo;
    uint32_t vao;
    uint32_t ebo;
};

struct Static
{
    uint32_t vbo;
    uint32_t vao;
    uint32_t ebo;
};

struct Dynamic
{
    uint32_t vbo;
    uint32_t vao;
    uint32_t ebo;
};

void SetupVboEbo(uint32_t &vbo, uint32_t &vao, uint32_t &ebo)
{
    //Setup a fullscreen quad
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), &quadIndices[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
}

Dynamic SetupDynamic()
{
    Dynamic renderable;

    SetupVboEbo(renderable.vbo, renderable.vao, renderable.ebo);

    return renderable;
}

Static SetupStatic(std::vector<glm::mat4> transforms)
{
    Static renderable;
    SetupVboEbo(renderable.vbo, renderable.vao, renderable.ebo);
    
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), &transforms[0], GL_STATIC_DRAW);

    glBindVertexArray(renderable.vao);
    // set attribute pointers for matrix (4 times vec4)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);

    return renderable;
}