#version 150

#pragma include "noise.glsl"
#pragma include "util.glsl"

out vec4 outputColor;
uniform vec4 globalColor;

uniform sampler2DRect u_fbtex1;

uniform float u_time;
uniform vec2 u_resolution;

#define OCTAVES 6
float fbm (in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .65;
    //
    // Loop of octaves
    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * noise(st);
        st *= 2.;
        amplitude *= .5;
    }
    return value;
}

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    
    vec2 dir = vec2(0.490,0.400);
    float s1 = fbm(st*4. +vec2(0.570,0.780) + u_time*dir );
    float s2 = fbm(st*4. +vec2(-0.430,0.420) + u_time*dir);
    
    float q1 = fbm(st*2. + vec2(s1,s2) + vec2(0.310,0.790) +u_time*0. );
    float q2 = fbm(st*2. + vec2(s1,s2) + vec2(-0.440,0.470) +u_time*0. );
    
    float r = fbm(st + vec2(q1,q2));
    
    vec3 color = vec3(0.0);
    color += r*globalColor.rgb;
    color = mix(color, vec3(0.959,0.980,0.990), q2);
    
    
	outputColor = vec4(color, globalColor.a);
}






