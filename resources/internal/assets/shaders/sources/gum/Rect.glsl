#stage vertex
#version 460 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inTexCoord;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec2 outUV;

layout (location = 2) out float outStrokeWidth;
layout (location = 3) out vec2 outArcSize;
layout (location = 4) out vec4 outStrokeColor;
layout (location = 5) flat out int outTextureIndex;



layout(push_constant) uniform PushConstants {
    float strokeWidth;
    int textureIndex;
    vec2 arcSize;
    vec4 fillColor;
    vec4 strokeColor;
    mat3 model;
} pc;

void main()
{

    mat3 model = pc.model;
    vec3 modelPos = model * vec3(inPosition.xy, 1.0);

    outColor = pc.fillColor;
    outUV = inTexCoord;
    outStrokeWidth = pc.strokeWidth;
    outArcSize = pc.arcSize;
    outStrokeColor = pc.strokeColor;
    outTextureIndex = pc.textureIndex;
    gl_Position = vec4(modelPos.xy, 0.0, 1.0);


}

#stage fragment
#version 460 core
layout (location = 0) in vec4 inFragColor;
layout (location = 1) in vec2 inUV;
layout (location = 2) in float inStrokeWidth;
layout (location = 3) in vec2 inArcSize;
layout (location = 4) in vec4 inStrokeColor;
layout (location = 5) flat in int inTextureIndex;

layout(location = 0) out vec4 outFragColor;

layout(set=2, binding = 0) uniform sampler2D u_Textures[32];


float ellipseDist(vec2 uv, vec2 center, vec2 radii)
{
    vec2 r = (max((abs(uv) - center+radii), vec2(0,0)) / radii);
    return (r.x*r.x + r.y*r.y);
}

vec4 getTexColor(int texIndex, vec2 texCoord, float tilingFactor)
{
    vec4 texColor = inFragColor;

    switch(int(texIndex))
    {
        case  0: texColor *= texture(u_Textures[ 0], texCoord * tilingFactor); break;
        case  1: texColor *= texture(u_Textures[ 1], texCoord * tilingFactor); break;
        case  2: texColor *= texture(u_Textures[ 2], texCoord * tilingFactor); break;
        case  3: texColor *= texture(u_Textures[ 3], texCoord * tilingFactor); break;
        case  4: texColor *= texture(u_Textures[ 4], texCoord * tilingFactor); break;
        case  5: texColor *= texture(u_Textures[ 5], texCoord * tilingFactor); break;
        case  6: texColor *= texture(u_Textures[ 6], texCoord * tilingFactor); break;
        case  7: texColor *= texture(u_Textures[ 7], texCoord * tilingFactor); break;
        case  8: texColor *= texture(u_Textures[ 8], texCoord * tilingFactor); break;
        case  9: texColor *= texture(u_Textures[ 9], texCoord * tilingFactor); break;
        case 10: texColor *= texture(u_Textures[10], texCoord * tilingFactor); break;
        case 11: texColor *= texture(u_Textures[11], texCoord * tilingFactor); break;
        case 12: texColor *= texture(u_Textures[12], texCoord * tilingFactor); break;
        case 13: texColor *= texture(u_Textures[13], texCoord * tilingFactor); break;
        case 14: texColor *= texture(u_Textures[14], texCoord * tilingFactor); break;
        case 15: texColor *= texture(u_Textures[15], texCoord * tilingFactor); break;
        case 16: texColor *= texture(u_Textures[16], texCoord * tilingFactor); break;
        case 17: texColor *= texture(u_Textures[17], texCoord * tilingFactor); break;
        case 18: texColor *= texture(u_Textures[18], texCoord * tilingFactor); break;
        case 19: texColor *= texture(u_Textures[19], texCoord * tilingFactor); break;
        case 20: texColor *= texture(u_Textures[20], texCoord * tilingFactor); break;
        case 21: texColor *= texture(u_Textures[21], texCoord * tilingFactor); break;
        case 22: texColor *= texture(u_Textures[22], texCoord * tilingFactor); break;
        case 23: texColor *= texture(u_Textures[23], texCoord * tilingFactor); break;
        case 24: texColor *= texture(u_Textures[24], texCoord * tilingFactor); break;
        case 25: texColor *= texture(u_Textures[25], texCoord * tilingFactor); break;
        case 26: texColor *= texture(u_Textures[26], texCoord * tilingFactor); break;
        case 27: texColor *= texture(u_Textures[27], texCoord * tilingFactor); break;
        case 28: texColor *= texture(u_Textures[28], texCoord * tilingFactor); break;
        case 29: texColor *= texture(u_Textures[29], texCoord * tilingFactor); break;
        case 30: texColor *= texture(u_Textures[30], texCoord * tilingFactor); break;
        case 31: texColor *= texture(u_Textures[31], texCoord * tilingFactor); break;
    }
    return texColor;
}
void main()
{
    vec2 uv = inUV * 2.0 - 1.0;
    vec2 radius = inArcSize;

    vec2 strokedBoxSize = vec2(1.0);
    vec2 innerBoxSize = strokedBoxSize - vec2(inStrokeWidth);

    float dist = ellipseDist(uv, strokedBoxSize, radius);
    float innerDist = ellipseDist(uv, innerBoxSize, radius);

    float edgeWidth = inStrokeWidth * 0.02; // this controls the width of the edge feathering
    float outerEdge = smoothstep(1.0, 1.0 + edgeWidth, dist);
    float innerEdge = smoothstep(1.0, 1.0 + edgeWidth, innerDist);

    vec4 fillColor = getTexColor(inTextureIndex, inUV, 1.0);

    vec4 finalColor = mix(inFragColor*fillColor, inStrokeColor, innerEdge);
    finalColor.a *= 1.0 - outerEdge;

    // DEBUG, don't remove yet
    /*if (finalColor.a < 0.001f)
    {
        finalColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }*/
    outFragColor = finalColor;


}