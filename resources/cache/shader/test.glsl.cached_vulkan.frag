#    &                 GLSL.std.450              
       main    
                         
    assets/shaders/temp/test.glsl    �    �     #version 460
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
}     
 GL_GOOGLE_cpp_style_line_directive    GL_GOOGLE_include_directive      main      
   outColor         texSampler       fragTexCoord         UniformColor             uColor       colorObj         PushConstants            colorBlend        colorBlendData  J entry-point main    J auto-map-bindings   J auto-map-locations  J client vulkan100    J target-env spirv1.6 J target-env vulkan1.3    J entry-point main    G  
          G     "       G     !      G           H         #       G        G     "       G     !      H         #       G             !                               	         ;  	   
       	                                                  ;                                   ;                               ;                       +                                      	      ;         	      !   	                 6               �                 =           =           W              >  
                  =        
   A              =           A  !   "          =     #   "   P     $   #   #   #   #        %      .         $   >  
   %   �  8  