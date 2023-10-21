#stage vertex
#version 460 core

void main()
{
    float x = -1.0 + float((gl_VertexIndex & 1) << 2);
    float y = 1.0 - float((gl_VertexIndex & 2) << 1);
    gl_Position = vec4(x, y, 0.0, 1.0);
}

#stage fragment
#version 460 core

layout(location = 0) out vec4 outColor;
void main()
{
    outColor = vec4(0.5, 0.0, 0.5, 1.0);
}