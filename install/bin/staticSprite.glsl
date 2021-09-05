#shader vertex
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 3) in mat4 instanceMatrix;

//out vec2 TexCoords;

in int gl_InstanceID;

out flat int instanceID;

uniform mat4 view;

void main()
{
    gl_Position = view * instanceMatrix * vec4(aPos, 1.0); 
    //TexCoords = aTexCoords;
    instanceID = gl_InstanceID;
}

#shader fragment
#version 430 core
out vec4 FragColor;

in flat int instanceID;

//in vec2 TexCoords;

//uniform sampler2D texture_diffuse1;

void main()
{
    if (instanceID > 10)
    {
	    FragColor = vec4((1.0/(instanceID * 0.001)), 0.0, 0.0, 0.5);
    }
    else
    {
        discard;
    }
}