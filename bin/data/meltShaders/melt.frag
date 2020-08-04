#version 150
#pragma include "noise.glsl"


uniform sampler2DRect tex0; ////this is "draw in the shader"
uniform sampler2DRect fbtex1;
uniform sampler2DRect fbtex2;
in vec2 varyingtexcoord;
out vec4 outputColor;
uniform vec2 WindowSize;
uniform float time;
uniform vec3 u_bColor;
uniform float u_val;

void main (void)
{
    vec2 uv = varyingtexcoord;
    
    vec4 t1 = texture(fbtex2,uv);
    uv.y += ( snoise(vec4( uv*.005,time*0.01, 5.))  )*1.5 *u_val;
    uv.x += ( snoise(vec4( uv*.005,time*0.01, 100.))  )*1.5 *u_val;
    
    //uv.x += ( snoise(vec3( uv*100.1, 5. )) )*0.5;
    //uv.y += ( snoise(vec3( uv*100.1, 100. )) )*0.5;
    /*
    vec2 uv2 = uv;
    uv.x += (uv2.y-300.)*0.01;
    uv.y += -(uv2.x-400.)*0.01;
    */
    vec4 t0 = texture(tex0,uv);
    
    vec4 col = mix(t0,t1,0.1);
    
    //col = mix(col,vec4(u_bColor,1.0),0.001);
    
    outputColor = col.rgba;

}
