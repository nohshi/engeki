#version 150
#pragma include "noise.glsl"

uniform sampler2DRect tex0; ////this is "draw in the shader"
uniform sampler2DRect fbtex1;
uniform sampler2DRect fbtex2;
in vec2 varyingtexcoord;
in vec4 varyingNormal;
in vec4 varyingPosition;
out vec4 outputColor;
uniform vec2 WindowSize;
uniform float u_time;
uniform vec3 u_bColor;
uniform float u_val;

uniform vec4 globalColor;



void main (void){
    
    vec2 uv = varyingtexcoord;
    float pct = (snoise(vec3(uv*5.,u_time)) + 1.) * 0.5;
    pct = step(pct, 0.6);
    if (pct < 0.001) {
        discard;
    }else{
        
        vec3 lightPos = normalize(vec3( 1.,-1.,1.5));
        float intensity;
        intensity = max(0.0, dot(lightPos, varyingNormal.xyz))*0.8 +0.2;
        //intensity = 1.;
        vec3 color = globalColor.rgb;
        float luminescence = length(varyingPosition)/250.;
        color = color * intensity;
        color.r = color.r  + luminescence;
        color.g = color.g  + luminescence*0.2;
        
        outputColor = vec4(color, 1.0);
    }
    

}
