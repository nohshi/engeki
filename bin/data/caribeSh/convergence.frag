#version 150


out vec4 outputColor;
uniform vec4 globalColor;
uniform sampler2DRect tex0; ////this is "draw in the shader"

uniform vec2 u_windowSize;
uniform float u_time;
uniform float u_audioVol;

in vec2 texCoordVarying;

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
    dist.x -= .2;
    return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(){
    vec2 st = texCoordVarying;
    //st.x *= u_windowSize.x/u_windowSize.y;
    //st = fract(st);
    //float pct = 0.0;
    
    float slide = 20 * u_audioVol;
    vec3 t0;
    t0.r = texture(tex0, st).r;
    t0.g = texture(tex0, vec2(st.x-slide,st.y)).g;
    t0.b = texture(tex0, vec2(st.x+slide,st.y)).b;

    
    outputColor = vec4( t0, globalColor.a );
}




