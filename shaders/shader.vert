#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float t;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
	Position = vec3(model * vec4(aPos.x,sin(aPos.x+aPos.z + t *0.02f),aPos.z, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}  
