#type vertex
#version 450 core

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 aPos;
layout(location = 1) out vec3 nearPoint;
layout(location = 2) out vec3 farPoint;
vec3 gridPlane[6] = vec3[](
vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}
void main()
{
    vec3 p = gridPlane[gl_VertexID].xyz;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, viewMatrix, projectionMatrix).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0, viewMatrix, projectionMatrix).xyz; // unprojecting on the far plane
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
}


#type fragment
#version 450 core
layout(location = 1) in vec3 nearPoint; // nearPoint calculated in vertex shader
layout(location = 2) in vec3 farPoint; // farPoint calculated in vertex shader
layout(location = 0) out vec4 outColor;

void main()
{
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    outColor = vec4(1.0, 0.0, 0.0, 1.0 * float(t>0)); // opacity = 1 when t > 0, opacity = 0 otherwise
}