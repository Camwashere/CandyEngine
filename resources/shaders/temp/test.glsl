#stage vertex
#version 460

/*
layout ( push_constant ) uniform constants
{
    mat4 model;
    mat4 view;
    mat4 proj;
} PushConstants;*/

layout(set=0, binding=0) uniform CameraBuffer
{
    //mat4 model;
    mat4 view;
    mat4 proj;

} cameraData;

struct ObjectData
{
    mat4 model;
};
layout(std140, set=1, binding=0) readonly buffer ObjectBuffer
{
    ObjectData objects[];
} objectBuffer;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;


void main() {
    mat4 modelMatrix = objectBuffer.objects[gl_BaseInstance].model;
    //mat4 modelMatrix = cameraData.model;
    mat4 transformMatrix = (cameraData.proj * cameraData.view * modelMatrix);
    gl_Position = transformMatrix * vec4(inPosition, 1.0f);
    //gl_Position = PushConstants.proj * PushConstants.view * PushConstants.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}

#stage fragment
#version 460
layout (push_constant) uniform PushConstants
{
    float colorBlend;
} colorBlendData;

layout(set=0, binding = 1) uniform UniformColor
{
    vec4 uColor;
} colorObj;
//layout(binding = 0) uniform vec4 uColor;
layout(set=0, binding = 2) uniform sampler2D texSampler;
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 0) out vec4 outColor;

void main() {

    // = vec4(fragTexCoord, 0.0, 1.0);
    outColor = texture(texSampler, fragTexCoord);
    outColor = mix(outColor, colorObj.uColor, colorBlendData.colorBlend);
}