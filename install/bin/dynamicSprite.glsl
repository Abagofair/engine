#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;

//out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0); 
    //TexCoords = aTexCoords;
}

#shader fragment
#version 430 core
out vec4 FragColor;

//in vec2 TexCoords;

//uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = vec4(0.0, 0.1, 0.8, 1.0);
}