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

layout(set=0, binding=0) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;

layout(push_constant) uniform PushConstants {
    int objectIndex;
    int textureIndex;
    float tilingFactor;
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
    outTextureIndex = pc.textureIndex;
    outTilingFactor = pc.tilingFactor;
}

#stage fragment
#version 460 core
layout(location = 0) in vec4 inColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) flat in int inTexIndex;
layout(location = 4) flat in float inTilingFactor;

layout(set=2, binding = 0) uniform sampler2D u_Textures[32];

layout(location = 0) out vec4 outColor;
void main()
{

    vec4 texColor = inColor;

    switch(int(inTexIndex))
    {
        case  0: texColor *= texture(u_Textures[ 0], fragTexCoord * inTilingFactor); break;
        case  1: texColor *= texture(u_Textures[ 1], fragTexCoord * inTilingFactor); break;
        case  2: texColor *= texture(u_Textures[ 2], fragTexCoord * inTilingFactor); break;
        case  3: texColor *= texture(u_Textures[ 3], fragTexCoord * inTilingFactor); break;
        case  4: texColor *= texture(u_Textures[ 4], fragTexCoord * inTilingFactor); break;
        case  5: texColor *= texture(u_Textures[ 5], fragTexCoord * inTilingFactor); break;
        case  6: texColor *= texture(u_Textures[ 6], fragTexCoord * inTilingFactor); break;
        case  7: texColor *= texture(u_Textures[ 7], fragTexCoord * inTilingFactor); break;
        case  8: texColor *= texture(u_Textures[ 8], fragTexCoord * inTilingFactor); break;
        case  9: texColor *= texture(u_Textures[ 9], fragTexCoord * inTilingFactor); break;
        case 10: texColor *= texture(u_Textures[10], fragTexCoord * inTilingFactor); break;
        case 11: texColor *= texture(u_Textures[11], fragTexCoord * inTilingFactor); break;
        case 12: texColor *= texture(u_Textures[12], fragTexCoord * inTilingFactor); break;
        case 13: texColor *= texture(u_Textures[13], fragTexCoord * inTilingFactor); break;
        case 14: texColor *= texture(u_Textures[14], fragTexCoord * inTilingFactor); break;
        case 15: texColor *= texture(u_Textures[15], fragTexCoord * inTilingFactor); break;
        case 16: texColor *= texture(u_Textures[16], fragTexCoord * inTilingFactor); break;
        case 17: texColor *= texture(u_Textures[17], fragTexCoord * inTilingFactor); break;
        case 18: texColor *= texture(u_Textures[18], fragTexCoord * inTilingFactor); break;
        case 19: texColor *= texture(u_Textures[19], fragTexCoord * inTilingFactor); break;
        case 20: texColor *= texture(u_Textures[20], fragTexCoord * inTilingFactor); break;
        case 21: texColor *= texture(u_Textures[21], fragTexCoord * inTilingFactor); break;
        case 22: texColor *= texture(u_Textures[22], fragTexCoord * inTilingFactor); break;
        case 23: texColor *= texture(u_Textures[23], fragTexCoord * inTilingFactor); break;
        case 24: texColor *= texture(u_Textures[24], fragTexCoord * inTilingFactor); break;
        case 25: texColor *= texture(u_Textures[25], fragTexCoord * inTilingFactor); break;
        case 26: texColor *= texture(u_Textures[26], fragTexCoord * inTilingFactor); break;
        case 27: texColor *= texture(u_Textures[27], fragTexCoord * inTilingFactor); break;
        case 28: texColor *= texture(u_Textures[28], fragTexCoord * inTilingFactor); break;
        case 29: texColor *= texture(u_Textures[29], fragTexCoord * inTilingFactor); break;
        case 30: texColor *= texture(u_Textures[30], fragTexCoord * inTilingFactor); break;
        case 31: texColor *= texture(u_Textures[31], fragTexCoord * inTilingFactor); break;
    }

    if (texColor.a == 0.0)
    discard;

    outColor = texColor;
}