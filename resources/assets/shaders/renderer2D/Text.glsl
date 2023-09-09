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

layout(set=2, binding=1) uniform sampler2D u_FontAtlas;

layout(location = 0) out vec4 outValue;

//const float pxRange = 10.0; // set to distance field's pixel range
layout(constant_id = 0) const float pxRange=10.0;
float screenPxRange() {

    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(inTexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(vec3 color) {
    return max(min(color.r, color.g), min(max(color.r, color.g), color.b));
}

void main()
{

    vec4 texColor = inColor * texture(u_FontAtlas, inTexCoord);

    vec3 sdTri = texture(u_FontAtlas, inTexCoord).rgb;
    float minSd = texture(u_FontAtlas, inTexCoord).a;

    // Since MT-SDF encodes distance in alpha, use it directly
    float screenPxDistance = screenPxRange()*(minSd - 0.5);

    //float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);

    // Make softness depend on alpha
    float opacity = smoothstep(0.2, 0.8, screenPxDistance + 0.5);

    if (opacity == 0.0)
    discard;

    outValue = mix(vec4(0.0), inColor, opacity);

    if (outValue.a == 0.0)
    discard;


}