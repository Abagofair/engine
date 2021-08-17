#shader vert
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in mat4 instanceMatrix;
//layout (location = 3) in mat4 instanceMatrix;

//out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0); 
    //TexCoords = aTexCoords;
}

#shader frag
#version 330 core
out vec4 FragColor;

//in vec2 TexCoords;

//uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = vec4(0.2, 0.5, 0.7, 1.0);
}