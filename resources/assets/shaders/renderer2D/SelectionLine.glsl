#stage vertex
#version 450 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in int entityID;

layout(set=0, binding=1) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;



layout (location = 0) out vec4 outColor;
layout (location = 1) out flat int outEntityID;

void main()
{
    gl_Position = cameraData.viewProjection * vec4(inPosition, 1.0f);
    outColor = inColor;
    outEntityID = entityID;
}

#stage fragment
#version 450 core

layout (location = 0) in vec4 color;
layout (location = 1) in flat int inEntityID;

layout(location = 0) out int outValue;

void main()
{
    outValue = inEntityID;
}