#version 150
#pragma include "noise.glsl"

uniform vec4 globalColor;

in vec2 varyingtexcoord;

out vec4 outputColor;

uniform float u_time;
 
void main(){
    vec2 uv = varyingtexcoord;
    vec2 uvSeed = uv * 0.001;
    float bubble = (snoise(vec2(uvSeed.x, uvSeed.y-u_time*0.9))+1.)*0.5;
    bubble = smoothstep(0.7, 0.8, bubble)*0.4;
    
    vec3 col = min(globalColor.rgb + bubble, 1.);
    
    col *= min(0.9+uv.y/1000., 1.);
    outputColor = vec4(col, .7);
}
