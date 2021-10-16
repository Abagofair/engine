#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 3) in mat4 instanceMatrix;

//out vec2 TexCoords;

in int gl_InstanceID;

out vec4 color;

out flat uint instanceID;

uniform mat4 view;

void main()
{
    gl_Position = view * instanceMatrix * vec4(aPos, 1.0);
    color = aColor;
    //TexCoords = aTexCoords;
    instanceID = gl_InstanceID;
}

    #shader fragment
    #version 430 core

uniform uint staticBlocks[512];

out vec4 FragColor;

in vec4 color;

in flat uint instanceID;

//in vec2 TexCoords;

//uniform sampler2D texture_diffuse1;

void main()
{
    if (staticBlocks[instanceID] == 1)
    {
        FragColor = color;
    }
    else
    {
        discard;
    }
}