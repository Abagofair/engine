#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color;
//out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0);
    color = aColor;
    //TexCoords = aTexCoords;
}

    #shader fragment
    #version 430 core

in vec4 color;

out vec4 FragColor;

//in vec2 TexCoords;

//uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = color;
}