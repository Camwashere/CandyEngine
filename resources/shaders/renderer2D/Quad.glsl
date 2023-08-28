#stage vertex
#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in float inTexIndex;
layout(location = 4) in float inTilingFactor;
layout(location = 5) in int entityID;



layout(set=0, binding=1) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;



layout(location = 0) out vec4 outColor;
layout(location = 1) out vec2 outTexCoord;
layout(location = 2) out float outTilingFactor;
layout(location = 3) out flat float outTexIndex;
layout(location = 4) out flat int outEntityID;

void main()
{
    gl_Position = cameraData.viewProjection * vec4(inPosition, 1.0f);

    outColor = inColor;
    outTexCoord = inTexCoord;
    outTilingFactor = inTilingFactor;
    outTexIndex = inTexIndex;
    outEntityID = entityID;
}

#stage fragment
#version 460 core

layout (location = 0) in vec4 inColor;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in float inTilingFactor;
layout (location = 3) in flat float inTexIndex;
layout (location = 4) in flat int inEntityID;

layout (set=2, binding = 0) uniform sampler2D u_Textures[32];

layout(location=0) out vec4 outColor;

void main()
{
    vec4 texColor = inColor;

    switch(int(inTexIndex))
    {
        case  0: texColor *= texture(u_Textures[ 0], inTexCoord * inTilingFactor); break;
        case  1: texColor *= texture(u_Textures[ 1], inTexCoord * inTilingFactor); break;
        case  2: texColor *= texture(u_Textures[ 2], inTexCoord * inTilingFactor); break;
        case  3: texColor *= texture(u_Textures[ 3], inTexCoord * inTilingFactor); break;
        case  4: texColor *= texture(u_Textures[ 4], inTexCoord * inTilingFactor); break;
        case  5: texColor *= texture(u_Textures[ 5], inTexCoord * inTilingFactor); break;
        case  6: texColor *= texture(u_Textures[ 6], inTexCoord * inTilingFactor); break;
        case  7: texColor *= texture(u_Textures[ 7], inTexCoord * inTilingFactor); break;
        case  8: texColor *= texture(u_Textures[ 8], inTexCoord * inTilingFactor); break;
        case  9: texColor *= texture(u_Textures[ 9], inTexCoord * inTilingFactor); break;
        case 10: texColor *= texture(u_Textures[10], inTexCoord * inTilingFactor); break;
        case 11: texColor *= texture(u_Textures[11], inTexCoord * inTilingFactor); break;
        case 12: texColor *= texture(u_Textures[12], inTexCoord * inTilingFactor); break;
        case 13: texColor *= texture(u_Textures[13], inTexCoord * inTilingFactor); break;
        case 14: texColor *= texture(u_Textures[14], inTexCoord * inTilingFactor); break;
        case 15: texColor *= texture(u_Textures[15], inTexCoord * inTilingFactor); break;
        case 16: texColor *= texture(u_Textures[16], inTexCoord * inTilingFactor); break;
        case 17: texColor *= texture(u_Textures[17], inTexCoord * inTilingFactor); break;
        case 18: texColor *= texture(u_Textures[18], inTexCoord * inTilingFactor); break;
        case 19: texColor *= texture(u_Textures[19], inTexCoord * inTilingFactor); break;
        case 20: texColor *= texture(u_Textures[20], inTexCoord * inTilingFactor); break;
        case 21: texColor *= texture(u_Textures[21], inTexCoord * inTilingFactor); break;
        case 22: texColor *= texture(u_Textures[22], inTexCoord * inTilingFactor); break;
        case 23: texColor *= texture(u_Textures[23], inTexCoord * inTilingFactor); break;
        case 24: texColor *= texture(u_Textures[24], inTexCoord * inTilingFactor); break;
        case 25: texColor *= texture(u_Textures[25], inTexCoord * inTilingFactor); break;
        case 26: texColor *= texture(u_Textures[26], inTexCoord * inTilingFactor); break;
        case 27: texColor *= texture(u_Textures[27], inTexCoord * inTilingFactor); break;
        case 28: texColor *= texture(u_Textures[28], inTexCoord * inTilingFactor); break;
        case 29: texColor *= texture(u_Textures[29], inTexCoord * inTilingFactor); break;
        case 30: texColor *= texture(u_Textures[30], inTexCoord * inTilingFactor); break;
        case 31: texColor *= texture(u_Textures[31], inTexCoord * inTilingFactor); break;
    }

    if (texColor.a == 0.0)
    discard;

    outColor = texColor;
    //o_EntityID = v_EntityID;

}