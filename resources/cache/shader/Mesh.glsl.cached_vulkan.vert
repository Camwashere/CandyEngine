#    E                 GLSL.std.450                      main             -   1   <   =   A   C        assets/shaders/renderer3D/Mesh.glsl  �    �     #version 460 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragTexCoord;

layout(set=0, binding=0) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;

} cameraData;

layout(push_constant) uniform PushConstants {
    int objectIndex;
} pc;

layout(std140, set=1, binding=0) readonly buffer ObjectBuffer
{
    mat4 transforms[];
} objectBuffer;

void main()
{

    mat4 modelMatrix = objectBuffer.transforms[pc.objectIndex];
    mat4 transformMatrix = (cameraData.proj * cameraData.view * modelMatrix);
    gl_Position = transformMatrix * vec4(inPosition, 1.0f);
    fragNormal = inNormal;
    fragTexCoord = inTexCoord;
}

   
 GL_GOOGLE_cpp_style_line_directive    GL_GOOGLE_include_directive      main         ObjectBuffer             transforms       objectBuffer         PushConstants            objectIndex      pc       CameraBuffer             view            proj         cameraData    +   gl_PerVertex      +       gl_Position   +      gl_PointSize      +      gl_ClipDistance   +      gl_CullDistance   -         1   inPosition    <   fragNormal    =   inNormal      A   fragTexCoord      C   inTexCoord  J entry-point main    J auto-map-bindings   J auto-map-locations  J client vulkan100    J target-env spirv1.6 J target-env vulkan1.3    J entry-point main    G        @   H            H            H         #       H               G        G     "      G     !       H         #       G        H            H         #       H               H           H        #   @   H              G        G     "       G     !       H  +              H  +            H  +            H  +            G  +      G  1          G  <          G  =         G  A         G  C              !                              	              	                       ;                       +                          	      ;        	         	               	        	   	               ;           +                     	     (           +  (   )        *      )     +         *   *      ,      +   ;  ,   -        /            0      /   ;  0   1      +     3     �?   9            ;      /   ;  ;   <      ;  0   =        ?            @      ?   ;  @   A         B      ?   ;  B   C                 6               �                 A              =           A                 =  	                     A      !         =  	   "   !   A      #         =  	   $   #   �  	   %   "   $   �  	   '   %                  =  /   2   1   Q     4   2       Q     5   2      Q     6   2      P     7   4   5   6   3   �     8   '   7   A  9   :   -      >  :   8               =  /   >   =   >  <   >                =  ?   D   C   >  A   D   �  8  