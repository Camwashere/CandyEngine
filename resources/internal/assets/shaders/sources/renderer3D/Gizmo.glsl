#stage vertex
#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;

layout(location = 0) out vec4 fragColor;

layout(set=0, binding=0) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;

layout(push_constant) uniform PushConstants {
    int objectIndex;
} pc;

layout(std140, set=1, binding=0) readonly buffer ObjectBuffer
{
    mat4 transforms[];
} objectBuffer;


void main()
{

    mat4 modelMatrix = objectBuffer.transforms[pc.objectIndex];
    mat4 transformMatrix = (cameraData.viewProjection * modelMatrix);
    gl_Position = transformMatrix * vec4(inPosition, 1.0f);
    fragColor = inColor;
}


#stage fragment
#version 460 core
layout(location = 0) in vec4 inColor;
layout(location = 0) out vec4 outColor;

void main()
{
    outColor = inColor;
}