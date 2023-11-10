#stage vertex
#version 460 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoord;



layout (location = 0) out vec4 outColor;
layout (location = 1) out vec2 outTexCoord;


layout(push_constant) uniform PushConstants {
    vec4 fillColor;
    //mat3 model;
} pc;
void main()
{
    //mat4 model = pc.model * cameraData.viewProjection;

    //vec3 modelPos = vec4(model * vec4(inPosition, 0.0, 1.0)).xyz;
    //vec3 modelPos = pc.model * vec3(inPosition, 1.0);
    vec3 modelPos = vec3(inPosition, 1.0);

    //vec4 modelPos = pc.model * vec4(inPosition, 0.0, 1.0);


    outColor = pc.fillColor;
    outTexCoord = inTexCoord;

    gl_Position = vec4(modelPos.xy, 0.0, 1.0);
}

#stage fragment
#version 460 core

layout (location = 0) in vec4 inColor;
layout (location = 1) in vec2 inTexCoord;

layout(set=2, binding=1) uniform sampler2D u_FontAtlas;

layout(location = 0) out vec4 outValue;

//const float pxRange = 10.0; // set to distance field's pixel range
//layout(constant_id = 0) const float pxRange=0;



void main()
{

    vec4 texColor =  texture(u_FontAtlas, inTexCoord);
    float intensity = texColor.r;
    outValue = texColor;
    //outValue = vec4(inColor.rgb, intensity);





}