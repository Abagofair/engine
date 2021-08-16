#include <Systems/SpriteRender.hpp>

SpriteRender::SpriteRender(
    unsigned int width,
    unsigned int height
) : renderWidth(width), renderHeight(height)
{
    viewMatrix = glm::ortho<float>(0, (float)width, (float)height, 0, -1.0f, 1.0f);
    Quad quad;
    
    //Setup a fullscreen quad
    glGenVertexArrays(1, &vbo);
    glGenBuffers(1, &vao);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad.vertices), quad.vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad.indices), quad.indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

SpriteRender::~SpriteRender()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &ebo);
}

//Do copy constructor
//Do move constructor / operator

void SpriteRender::Draw(entt::registry &registry)
{
    auto view = registry.view<
        const SpriteComponent,
        const Texture2DComponent,
        const TransformComponent>();
    
    uint32_t instanceCount = 0;

    //TODO: Should probably find a way to get the actual shader program
    uint32_t shaderId = 0;

    //include multiple textures at shader initialization to the shader so all we have to do is pass in the textureid
    //

    //spriteShader.UseWithOrtho(viewMatrix);
    glUseProgram(shaderId);
    for (auto entity : view)
    {
        //auto &sprite = view.get<const SpriteComponent>(entity);
        //auto &texture = view.get<const Texture2DComponent>(entity);

        //during entity update loop we update the transform if data has changed
        auto &transform = view.get<const TransformComponent>(entity);

        //how to cache transform?
        //auto identity = glm::identity();
    }

    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instanceCount);
    glBindVertexArray(0);
}