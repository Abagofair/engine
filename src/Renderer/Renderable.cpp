#include <Renderer/Renderable.hpp>

using namespace Renderables;

void Renderables::SetupVboEbo(uint32_t &vbo, uint32_t &vao, uint32_t &ebo, float width, float height)
{
    float quadVertices[12] = 
    {
        width,  height, 0.0f,
        width, -height, 0.0f,
        -width, -height, 0.0f,
        -width,  height, 0.0f,
    };

    unsigned int quadIndices[6] =
    {
        0, 1, 3,
        1, 2, 3
    };

    //Setup a fullscreen quad
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), &quadIndices[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
}

Dynamic Renderables::SetupDynamic(uint32_t shaderId, uint32_t width, uint32_t height)
{
    Dynamic renderable;
    renderable.shaderId = shaderId;

    Renderables::SetupVboEbo(renderable.vbo, renderable.vao, renderable.ebo,
        (float)width, (float)height);

    return renderable;
}

Static Renderables::SetupStatic(uint32_t shaderId, std::vector<glm::mat4> transforms, uint32_t width, uint32_t height)
{
    Static renderable;
    Renderables::SetupVboEbo(renderable.vbo, renderable.vao, renderable.ebo,
        (float)width, (float)height);
    renderable.shaderId = shaderId;
    renderable.instances = transforms.size();
    
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