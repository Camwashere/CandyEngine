#                     GLSL.std.450                     main    
                      assets/shaders/renderer3D/Mesh.glsl  J    �     #version 460 core

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;

layout(set=2, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;
void main()
{
    outColor = texture(texSampler, fragTexCoord);
}   
 GL_GOOGLE_cpp_style_line_directive    GL_GOOGLE_include_directive      main      
   outColor         texSampler       fragTexCoord    J entry-point main    J auto-map-bindings   J auto-map-locations  J client vulkan100    J target-env spirv1.6 J target-env vulkan1.3    J entry-point main    G  
          G     "      G     !       G                !                               	         ;  	   
       	                                                  ;                                   ;                	      6               �                 =           =           W              >  
      �  8  