#version 150


in vec2 varyingtexcoord;
out vec4 outputColor;
uniform vec2 u_windowSize;
uniform float u_time;
uniform float u_asahiY;

float sunshine(in vec2 _st){
    vec2 dist = _st;
    float val = dot(dist,dist);
    
    return min((0.044+sin(u_time*2.)*0.005)/val ,2.416);
}

float sunlight(in vec2 _st){
    vec2 dist = _st;
    float val = dot(dist,dist);

    return min(0.148/val ,0.640);
}

float subSunlight(in vec2 _st){
    vec2 dist = _st;
    float val = dot(dist,dist);
    
    return min(0.724/val ,0.140);
}

void main (void){   
    vec2 st = gl_FragCoord.xy/u_windowSize;
    st = 1.-st;
    float ratioWH = u_windowSize.x/u_windowSize.y; //縦横の比率
    st.x *= ratioWH;
    
    st -= vec2(ratioWH*0.5,u_asahiY);
    vec3 color = vec3(0.);
    color = vec3(sunshine(st));
    color += vec3(sunlight(st));
    color += vec3(subSunlight(st));
    color *= vec3(0.940,0.718,0.155);
    color = min(color ,1.);
    color -= 0.200;
    color = max(color, 0.);
    
    
    outputColor = vec4(color,1.0);

}
