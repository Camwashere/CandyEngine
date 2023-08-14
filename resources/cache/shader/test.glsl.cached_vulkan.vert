#    C              K       GLSL.std.450                      main             +   /   :   ;   ?   A    
    assets/shaders/temp/test.glsl       �     #version 460

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

     
 GL_GOOGLE_cpp_style_line_directive    GL_GOOGLE_include_directive      main         ObjectData           model        ObjectBuffer             objects      objectBuffer         gl_BaseInstance      CameraBuffer             view            proj         cameraData    )   gl_PerVertex      )       gl_Position   )      gl_PointSize      )      gl_ClipDistance   )      gl_CullDistance   +         /   inPosition    :   fragColor     ;   inColor   ?   fragTexCoord      A   inTexCoord  J entry-point main    J auto-map-bindings   J auto-map-locations  J client vulkan100    J target-env spirv1.6 J target-env vulkan1.3    J entry-point main    H            H         #       H               G        @   H            H         #       G        G     "      G     !       G        I  H            H         #       H               H           H        #   @   H              G        G     "       G     !       H  )              H  )            H  )            H  )            G  )      G  /          G  :          G  ;         G  ?         G  A              !                              	              	                               ;                       +                        ;                    	        	   	               ;           +                    	     &           +  &   '        (      '     )         (   (      *      )   ;  *   +        -            .      -   ;  .   /      +     1     �?   7            9      -   ;  9   :      ;  .   ;        =            >      =   ;  >   ?         @      =   ;  @   A           $      6               �          %       =           A                    =  	              '       A              =  	          A     !         =  	   "   !   �  	   #       "   �  	   %   #           (       =  -   0   /   Q     2   0       Q     3   0      Q     4   0      P     5   2   3   4   1   �     6   %   5   A  7   8   +      >  8   6        *       =  -   <   ;   >  :   <        +       =  =   B   A   >  ?   B   �  8  