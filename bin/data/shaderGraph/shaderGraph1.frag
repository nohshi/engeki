#version 150

#pragma include "noise.glsl"
//#pragma include "util.glsl"

out vec4 outputColor;

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_val;
uniform vec4 globalColor;

void main(){

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    
    vec3 color = vec3(0.);
    vec3 orange = vec3(1.000,0.310,0.117);
    vec3 blue = vec3(0.443,0.503,0.845);
    
    color = mix( orange, blue, st.y+0.425 );
    color += ( 0.480 + snoise( vec2(st.y*5.680 - u_time*.25, u_time*.25) ) * 0.364 )/2.;

    outputColor = vec4(color,globalColor.a);
}
