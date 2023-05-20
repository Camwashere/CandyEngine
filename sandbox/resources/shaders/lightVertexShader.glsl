#version 430 core
in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
