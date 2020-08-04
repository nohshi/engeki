#version 150

#pragma include "noise.glsl"
#pragma include "util.glsl"

uniform vec2 u_windowSize;
uniform vec2 u_mouse;
uniform float u_time;

out vec4 outputColor;
uniform vec4 globalColor;

float plot(vec2 st, float pct){
  return  smoothstep( pct, pct-0.332, st.y*1.552);
          //-smoothstep( pct, pct+0.02, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_windowSize;

    float eTime = u_time * 0.6;
    // Smooth interpolation between 0.1 and 0.9
    float size = 0.05;
    float y = (snoise(vec2(st.x*10.+eTime*0.,eTime))+1.)*size+0.1;
    float y2 = (snoise(vec2(st.x*10.-eTime*0.,eTime))+1.)*size+0.1;
    
	vec3 color = vec3(0);
    float pct = plot(st, y);
    color += pct;
	float pct2 = plot(1.-st, y2);
    color += pct2;
    outputColor = vec4(vec3(113, 255, 250)/255.,color.r*globalColor.a);
}


