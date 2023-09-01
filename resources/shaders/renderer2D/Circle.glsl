#stage vertex
#version 460 core

// Vertex Shader
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in float inThickness;
layout(location = 4) in float inFade;
layout(location = 5) in int entityID;

layout(set=0, binding=1) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;



layout (location = 0) out vec4 outColor;
layout (location = 1) out vec2 outTexCoord;
layout (location = 2) out float outThickness;
layout (location = 3) out float outFade;
layout (location = 4) out flat int outEntityID;
layout (location = 5) out vec4 outWorldPos;
layout(location = 6) out vec4 outLocalPos;

void main()
{
    outLocalPos = vec4(inPosition, 1.0f);
    outWorldPos = cameraData.viewProjection * vec4(inPosition, 1.0f);
    gl_Position = outWorldPos;
    outColor = inColor;
    outTexCoord = inTexCoord;
    outThickness = inThickness;
    outFade = inFade;
    outEntityID = entityID;

}

#stage fragment
#version 460 core

layout (location = 0) in vec4 inColor;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in float inThickness;
layout (location = 3) in float inFade;
layout (location = 4) in flat int inEntityID;
layout (location = 5) in vec4 inWorldPos;
layout (location = 6) in vec4 inLocalPos;

layout(location = 0) out vec4 outColor;



void main()
{
    vec2 center = vec2(0.5, 0.5);
    float distance = length(texCoord.xy - center);
    float circle = smoothstep(0.0, inFade, distance);
    circle *= smoothstep(inThickness + inFade, inThickness, distance);
    if (circle == 0)
    {
        discard;
    }
    outColor = inColor;
    outColor.a *= circle;


}