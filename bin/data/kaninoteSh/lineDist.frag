#version 150

#pragma include "noise.glsl"
#pragma include "util.glsl"

out vec4 outputColor;
uniform vec4 globalColor;

uniform float u_time;
uniform vec2 u_resolution;
uniform sampler2DRect u_img;
uniform float u_wind;
uniform float u_speed;

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.y = 1.-st.y;
    st.x *= u_resolution.x/u_resolution.y;
    
    vec3 color = vec3(0.0);
    
    // Scale the space in order to see the function
    float scale = 10.968;
    //st -= 0.5;
    float angle = nSsnoise(st*2.5+u_time*0.1)*PI*2.* u_wind;
    st = rotate2d(angle) * st;
    //st += 0.5;
    st *= scale;
    st.x += u_time*8.;
    vec2 sta = st;
    sta = fract(sta);
    float pct = step(sta.x, nSsnoise(vec2(floor(st.x),1.304)));
    pct *= step(st.y,scale*nSsnoise(vec2(floor(st.x),10.432+u_time*0.1)));
    
    vec2 uv = gl_FragCoord.xy;
    uv -= u_resolution/2.;
    angle = nSsnoise(uv/u_resolution.xy*4.5+u_time*0.6)*PI*2.* u_wind;
    uv = rotate2d(angle) * uv;
    uv += u_resolution/2.;
    vec3 t1 = texture(u_img, uv).rgb;
    
    color = vec3(pct) * t1;
    
    
	outputColor = vec4(color, globalColor.a);
}






