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
    //TexCoords = aTexCoords;
}

    #shader fragment
    #version 430 core
out vec4 FragColor;

in vec4 color;
in vec2 tex;

uniform sampler2D texture1;

//in vec2 TexCoords;

//uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = mix(texture(texture1, tex), color, 1.0);
}