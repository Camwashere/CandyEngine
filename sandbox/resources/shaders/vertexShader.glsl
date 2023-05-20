#version 430 core

in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model*vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model)))*aNormal;
    TexCoord = aTexCoord;
    gl_Position = projection*view*vec4(FragPos, 1.0);

}