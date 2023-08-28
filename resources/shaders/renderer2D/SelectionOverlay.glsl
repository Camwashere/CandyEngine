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
layout(location = 3) flat out float outTexIndex;
layout(location = 4) flat out int outEntityID;
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
layout (location = 3) flat in float inTexIndex;
layout (location = 4) flat in int inEntityID;

layout (location = 0) out int outValue;

void main()
{
    outValue = inEntityID;

}