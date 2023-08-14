#    ±                 GLSL.std.450                      main    ?   E   H   \   n   w   y   |           assets/shaders/renderer3D/Grid.glsl  B   Ì     #version 460 core




layout(location = 0) out float near;
layout(location = 1) out float far;
layout(location = 2) out vec3 nearPoint;
layout(location = 3) out vec3 farPoint;
layout(location = 4) out mat4 fragView;
layout(location = 8) out mat4 fragProj;

layout(set=0, binding=0) uniform CameraBuffer
{
    mat4 view;
    mat4 proj;

} cameraData;

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

    vec3 p = gridPlane[gl_VertexIndex].xyz;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, cameraData.view, cameraData.proj).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0, cameraData.view, cameraData.proj).xyz; // unprojecting on the far plane
    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
    near = 0.01;
    far = 100;
    fragView = cameraData.view;
    fragProj = cameraData.proj;


}


  
 GL_GOOGLE_cpp_style_line_directive    GL_GOOGLE_include_directive      main         gridPlane     ?   gl_VertexIndex    E   nearPoint     F   CameraBuffer      F       view      F      proj      H   cameraData    \   farPoint      l   gl_PerVertex      l       gl_Position   l      gl_PointSize      l      gl_ClipDistance   l      gl_CullDistance   n         w   near      y   far   |   fragView         fragProj    J entry-point main    J auto-map-bindings   J auto-map-locations  J client vulkan100    J target-env spirv1.6 J target-env vulkan1.3    J entry-point main    G  ?      *   G  E         H  F          H  F       #       H  F             H  F         H  F      #   @   H  F            G  F      G  H   "       G  H   !       G  \         H  l              H  l            H  l            H  l            G  l      G  w          G  y         G  |         G                !                   	           
   	                              +                      +          ?+            ,                 +          ¿,                 ,                 ,                  , 	    !                         ;           =             >      =   ;  >   ?         D         ;  D   E        F   
   
      G      F   ;  G   H      +  =   I       +  =   J      +     P         U      
   ;  D   \        k      P     l   	      k   k      m      l   ;  m   n         t      	      v         ;  v   w      +     x   
×#<;  v   y      +     z     ÈB   {      
   ;  {   |      ;  {            °                    6               = ø     ;  °                     >     !        "       =  =   @   ?   A  ;   B      @   =     C   B        #       Q     N   C       Q     R   C      A  U   V   H   I   =  
   W   V   A  U   Y   H   J   =  
   Z   Y                 
         "   W                 
         "   Z                 
            P  	      N   R           	                        O                        Q              P                                    #       >  E                  P  	   ¨   N   R           	   ©      ¨               O     «   ©   ©             Q     ­   ©      P     ®   ­   ­   ­        ¯   «   ®        $       >  \   ¯        %       Q     r   C      P  	   s   N   R   r      A  t   u   n   I   >  u   s        &       >  w   x        '       >  y   z        (       >  |   W        )       >     Z   ý  8  