#version 150
#pragma include "noise.glsl"

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

out vec2 varyingtexcoord;

// the time value is passed into the shader by the OF app.
uniform float u_time;


void main()
{
    // the sine wave travels along the x-axis (across the screen),
    // so we use the x coordinate of each vertex for the calculation,
    // but we displace all the vertex along the y axis (up the screen)/
    float displacementHeight = 100.0;
    //float displacementY = sin(time + (position.x / 100.0)) * displacementHeight;
    vec4 pos = position;
    vec4 a_pos = position*0.002;
    float time = u_time * 0.9;
    float displacementY = snoise(vec2(a_pos.x ,a_pos.y-u_time)) * displacementHeight;
    pos.z += displacementY;///2  + snoise(vec2(a_pos.x*0.2 ,a_pos.y*0.2-u_Atime)) * 200;
    vec4 modifiedPosition = modelViewProjectionMatrix * pos;
	gl_Position = modifiedPosition;
    
    varyingtexcoord = position.xy;
}
