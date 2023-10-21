#stage vertex
#version 460 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec4 inColor;

layout (location = 0) out vec4 outColor;

layout(push_constant) uniform PushConstants {
    mat3 model;
} pc;
void main()
{
    mat3 model = pc.model;
    vec3 modelPos = model * vec3(inPosition.xy, 1.0);
    outColor = inColor;
    gl_Position = vec4(modelPos.xy, 0.0, 1.0);
    //gl_Position.y *= -1.0f;
}

#stage fragment
#version 460 core
layout (location = 0) in vec4 inFragColor;
layout(location = 0) out vec4 outFragColor;
void main()
{
    outFragColor = inFragColor;
}