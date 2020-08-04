#version 150
#define PI 3.14159265359

out vec4 outputColor;
uniform vec4 globalColor;
uniform sampler2DRect tex0; ////this is "draw in the shader"

in vec2 varyingtexcoord;

uniform vec2 u_resolution;
uniform float u_time;


mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

//https://iquilezles.org/www/articles/distfunctions2d/distfunctions2d.htm
float sdBox( in vec2 p, in vec2 b ){
    vec2 d = abs(p)-b;
    return length(max(d,vec2(0))) + min(max(d.x,d.y),0.0);
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

void main(){
    vec2 st = varyingtexcoord;
    st *= 1.;
    
    vec3 color = vec3(0.0);
    
    st -= 0.5;

    
    float rect = sdBox(st,vec2(1.)*u_time*0.4);
    float rectAmp = 5.;
    rect *= rectAmp;
    float rectShape = fract(rect);
    
    rectShape = step(rectShape, .8);
    color += vec3( rectShape );
    
    
    float sT = fract( -u_time*0. + floor(rect)/rectAmp );
    color *= myGrad(sT);
    
    color = min(color ,1.);
    
    
    if (color.r<0.001) {
        discard;
    }else{
        outputColor = vec4(color,1.0);
    }
}




