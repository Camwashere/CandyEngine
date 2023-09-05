#stage vertex
#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in int inEntityID;

layout(set=0, binding=1) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;
    mat4 viewProjection;

} cameraData;



layout (location = 0) out vec4 outColor;
layout (location = 1) out vec2 outTexCoord;
layout (location = 2) out flat int outEntityID;

void main()
{
    gl_Position = cameraData.viewProjection * vec4(inPosition, 1.0);

    outColor = inColor;
    outTexCoord = inTexCoord;
    outEntityID = inEntityID;
}

#stage fragment
#version 460 core

layout (location = 0) in vec4 inColor;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in flat int inEntityID;

layout (set=2, binding = 0) uniform sampler2D u_Textures[32];

layout(location = 0) out vec4 outValue;


float screenPxRange() {
    const float pxRange = 2.0; // set to distance field's pixel range
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_Textures[0], 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(inTexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    vec4 texColor = inColor * texture(u_Textures[0], inTexCoord);


    vec3 msd = texture(u_Textures[0], inTexCoord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    if (opacity == 0.0)
        discard;

    vec4 bgColor = vec4(0.0);
    outValue = mix(bgColor, inColor, opacity);
    if (outValue.a == 0.0)
        discard;


}