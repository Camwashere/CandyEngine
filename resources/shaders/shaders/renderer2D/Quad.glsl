#stage vertex
#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;



layout(set=0, binding=1) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;


layout(location = 0) out vec4 outColor;
void main()
{
    gl_Position = cameraData.viewProjection * vec4(inPosition, 1.0f);

    outColor = inColor;
}

#stage fragment
#version 460 core

layout (location = 0) in vec4 inColor;
layout(location=0) out vec4 outColor;

void main()
{
    vec4 texColor = inColor;
    outColor = texColor;

}