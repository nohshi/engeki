#version 150


in vec2 varyingtexcoord;
out vec4 outputColor;
uniform vec2 u_windowSize;
uniform float u_edge;


void main (void){   
    vec2 st = gl_FragCoord.xy/u_windowSize;
    st.y = 1.-st.y;
    float ratioWH = u_windowSize.x/u_windowSize.y; //縦横の比率
    st.x *= ratioWH;
    
    float alfa = (st.y + u_edge*1.5)*2 -2;
    
    outputColor = vec4(0.,0.,0., alfa);

}
