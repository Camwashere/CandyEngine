#stage vertex
#version 460 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec2 inTexCoord;


layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) flat out int outTextureIndex;
layout(location = 4) flat out float outTilingFactor;
layout(location = 5) flat out int outEntityID;

layout(set=0, binding=0) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;

layout(push_constant) uniform PushConstants {
    int objectIndex;
    int entityID;
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
    fragNormal = inNormal;
    fragTexCoord = inTexCoord;
    outTextureIndex = 0;
    outTilingFactor = 1.0;
    outEntityID = pc.entityID;
}

#stage fragment
#version 460 core
layout(location = 0) in vec4 inColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) flat in int inTexIndex;
layout(location = 4) flat in float inTilingFactor;
layout(location = 5) flat in int inEntityID;


layout(location = 0) out int outValue;
void main()
{

    outValue = inEntityID;
}