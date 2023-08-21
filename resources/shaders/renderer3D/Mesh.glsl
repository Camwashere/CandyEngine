#stage vertex
#version 460 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragTexCoord;

layout(set=0, binding=0) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;

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
    mat4 transformMatrix = (cameraData.proj * cameraData.view * modelMatrix);
    gl_Position = transformMatrix * vec4(inPosition, 1.0f);
    fragNormal = inNormal;
    fragTexCoord = inTexCoord;
}

#stage fragment
#version 460 core

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;

layout(set=2, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;
void main()
{
    outColor = texture(texSampler, fragTexCoord);
}