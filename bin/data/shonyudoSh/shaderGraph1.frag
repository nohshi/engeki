#version 150

#pragma include "noise.glsl"
#pragma include "util.glsl"

out vec4 outputColor;
uniform vec4 globalColor;

uniform vec2 u_windowSize;
uniform float u_time;
uniform vec2 u_bPos[10];

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
    dist.x -= .2;
    return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(){
    vec2 st = gl_FragCoord.xy/u_windowSize.xy;
    st.x *= u_windowSize.x/u_windowSize.y;
    st.x -= u_windowSize.x/u_windowSize.y*0.5;
    st.y -= 0.5;
    st = rotate2d(u_time*0.3) * st;
    st.x += u_windowSize.x/u_windowSize.y*0.5;
    st.y += 0.5;
    
    //st = fract(st);
    float pct = 0.0;
    vec3 sum = vec3(0.);
    float time = u_time * 0.3;
    
    vec3 color = vec3(0.);
     /*
    color = vec3(circle(st,1.5 + snoise(st+u_time*0.1)*0.2));
    color = 1.-color;
    color = clamp(color, 0.,1.);
     */
    // c. The SQUARE ROOT of the vector
    //    from the pixel to the center
    /*
    for(float i=0.; i<10.; i++){
        vec2 tC = st -vec2(.7);
        tC.x += snoise(vec2(time,i*5.))*.6;
        tC.y += snoise(vec2(time,i*10.))*.6;
        pct = dot(tC,tC)*1.;
        //pct = clamp(1.-pct ,-.0,1000.);
        sum += vec3(.0076/pct);
        //color = clamp(color, -.5,100.928);
    }*/
    int i;
    vec2 tC;
    float bSize = 1.; //ballSize
    float amplitude = 0.1;
    
    i = 0;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    i++;
    tC = st -u_bPos[i];
    tC.x += snoise(vec2(time,i*5.))* amplitude;
    tC.y += snoise(vec2(time,i*10.))* amplitude;
    pct = dot(tC,tC)* ( .5+snoise(vec2(time*2.,i))*snoise(vec2(time*2.,i))*3. );
    sum += vec3(.0076/pct);
    
    /*
    color += step( 1.040,sum);
    color -= step( 1.128,sum);
    color += step( 1.496,sum);
    */
    
    float size = -0.211;
    color += smoothstep(size + 0.378,size + 1.048, sum.r);
    size = 0.202;
    color -= smoothstep(size + .45,size + 1.056, sum.r);
    size = 0.284;
    color += smoothstep(size + .45,size + 1.368, sum.r);
    size = 1.652;
    color -= smoothstep(size + 0.250,size + 3.304, sum.r);
    color *= vec3(100, sum.r*250, sum.r*200)/255.;
    //color = sum;
    
    outputColor = vec4( color, globalColor.a );
}




