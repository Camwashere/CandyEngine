#stage vertex
#version 460 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoord;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec2 outUV;

layout (location = 2) out float outStrokeWidth;
layout (location = 3) out vec2 outArcSize;
layout (location = 4) out vec4 outStrokeColor;

layout(push_constant) uniform PushConstants {
    float strokeWidth;
    vec2 arcSize;
    vec4 strokeColor;
    mat3 model;
} pc;
void main()
{

    mat3 model = pc.model;
    vec3 modelPos = model * vec3(inPosition.xy, 1.0);

    outColor = inColor;
    outUV = inTexCoord;
    outStrokeWidth = pc.strokeWidth;
    outArcSize = pc.arcSize;
    outStrokeColor = pc.strokeColor;
    gl_Position = vec4(modelPos.xy, 0.0, 1.0);


}

#stage fragment
#version 460 core
layout (location = 0) in vec4 inFragColor;
layout (location = 1) in vec2 inUV;
layout (location = 2) in float inStrokeWidth;
layout (location = 3) in vec2 inArcSize;
layout (location = 4) in vec4 inStrokeColor;

layout(location = 0) out vec4 outFragColor;



float ellipseDist(vec2 uv, vec2 center, vec2 radii)
{
    vec2 r = (max((abs(uv) - center+radii), vec2(0,0)) / radii);
    return (r.x*r.x + r.y*r.y);
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

    vec4 finalColor = mix(inFragColor, inStrokeColor, innerEdge);
    finalColor.a *= 1.0 - outerEdge;

    // DEBUG, don't remove yet
    /*if (finalColor.a < 0.001f)
    {
        finalColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }*/
    outFragColor = finalColor;


}