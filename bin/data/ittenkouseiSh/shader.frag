#version 150
#pragma include "noise.glsl"
#define PI 3.14159265359


// the time value is passed into the shader by the OF app.
uniform float u_time;
uniform float u_time2;
uniform float u_amp;
uniform float u_Atime;
uniform vec2 u_windowSize;
uniform int u_state;
uniform float u_midi0;

uniform sampler2DRect u_aTex;

in vec2 varyingtexcoord;
out vec4 outputColor;

uniform vec4 globalColor;

// 指定した大きさの四角を描く関数
float box(vec2 st, float size) {
    size = 0.5 + size * 0.5;
    st.x = step(st.x,size) * step(1.0 - st.x,size);
    st.y = step(st.y,size) * step(1.0 - st.y,size);
    
    float outPut = st.x * st.y;
    return outPut;
}


vec3 myGrad(float p){
    vec3 orange = vec3(0.980,0.464,0.167);
    vec3 yellow = vec3(1.,1.,0.);
    vec3 green = vec3(.2, 1., 0.);
    vec3 blue = vec3(0, .22, 1.);
    
    p = fract(p);
    p = p * 3.;
    vec3 col;
    if(0.<=p && p<.5){
        col = mix(orange, yellow ,fract(p)*2.);
    }else if(.5<=p && p<1.5){
        col = mix(yellow, green ,fract(p-.5));
    }else if(1.5<=p && p<2.5){
        col = mix(green, blue ,fract(p-.5));
    }else if(2.5<=p && p<=3.){
        col = mix(blue, orange ,(fract(p)-0.5)*2.);
    }
    return col;
}

mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

float gradCurtain(vec2 _st){
    _st = rotate2d(29.088) * _st;
    _st += 1.;
    float a = -(u_midi0*1.5)+.4;//-1.608;
    float r = smoothstep(0.+a, _st.x+a, 0.288)-smoothstep(0.+0.5+a, _st.x+0.5+a, 0.288);
    return r;
}

float gradCurtain2(vec2 _st){
    _st = rotate2d(29.088) * _st;
    _st += 1.;
    float a = -(u_midi0*1.5)+.4;//-1.608;
    float r = smoothstep(0.+a, _st.x+a, 0.288);
    return r;
}
 
void main(){
    
    vec2 st = gl_FragCoord.xy/u_windowSize.xy;
    st.x *= u_windowSize.x/u_windowSize.y;
    //vec3 audioIn = texture(u_aTex,st).rgb;
    /*
    st.x = varyingtexcoord.x/u_windowSize.y;
    st.y = varyingtexcoord.y/u_windowSize.x;
    */
    vec3 color = vec3(0.0);
    float amp = 15.;
    st *= amp;
    float cVal = gradCurtain(floor(st)/amp);
    float cVal2 = gradCurtain2(floor(st)/amp);
    vec2 sta = fract(st);
    if (u_state==4) {
        sta -= vec2(0.5);
        sta = rotate2d( cVal2*PI*2. ) * sta;
        sta += vec2(0.5);
    }
    
    float s;
    if (u_state==1) {
        s = snoise( vec2(floor(st.x)+u_time*0.548, 0.3) );
    }else if(u_state==2 || u_state==3 || u_state==4) {
        s = snoise( vec2(floor(st.y)+u_time*0.548, 0.3) );
    }
    float s2 = random( vec2(floor(st.x)*0.01,floor(st.y)*0.01) );
    
    if (u_state==3) {
        color += vec3( box(sta,0.820 *abs(sin(s2+u_time2*5.))) );
    }else if(u_state==4){
        color += vec3( box(sta,0.820*cVal) );
    }else{
        color += vec3( box(sta,0.820) );
    }
    
    
    //vec3 sT = vec3(s + sPlus*0.8);
    float sT = s ; //sin(floor(st.x));//sPlus*0.8;
    //color *= hsb2rgb( vec3(sT.x*0.2,1.,1.) );
    color *= myGrad(sT);
    //color *= sT + sin(u_time*0.1);
    color = clamp(color,0.,1.);
    
    
    outputColor = vec4(color,globalColor.a);
}




