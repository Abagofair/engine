#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

out vec4 color;
out vec2 tex;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = view * model * vec4(aPos.xyz, 1.0);
    color = aColor;
    tex = aTex;
}

    #shader fragment
    #version 430 core
out vec4 FragColor;

in vec4 color;
in vec2 tex;

uniform bool useTexture;
uniform sampler2D texture1;

void main()
{
    if (useTexture)
    {
        vec4 sampledTexture = texture(texture1, tex);
        FragColor = vec4(color.xyz * sampledTexture.xyz, sampledTexture.w);
    }
    else
    {
        FragColor = color;
    }
}