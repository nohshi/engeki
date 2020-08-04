#version 150
#pragma include "noise.glsl"

// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;
// this is the end of the default functionality

// this is something we're creating for this shader
out vec2 varyingtexcoord;
out vec4 varyingNormal;
out vec4 varyingPosition;

// this is coming from our C++ code
//uniform float mouseX;
uniform vec2 mouse;
uniform float u_time;
uniform float u_scale;

float time = u_time * 5.;
float noiseScale = 0.008;
mat4 modifyMat4(vec3 _pos){ //平行移動
    mat4 modelMat = mat4( 1., 0., 0., 0.,
                          0., 1., 0., 0.,
                          0., 0., 1., 0.,
                          0., 0., 0., 1. );
    _pos *= noiseScale;
    modelMat[3][0] = snoise( vec3(time, _pos.y, _pos.z) );
    modelMat[3][1] = snoise( vec3(_pos.x, time, _pos.z) );
    modelMat[3][2] = snoise( vec3(_pos.x, _pos.y, time) );
    
    modelMat[3][0] *= u_scale;
    modelMat[3][1] *= u_scale;
    modelMat[3][2] *= u_scale;
    return modelMat;
}

mat4 scaleMat4(vec3 _pos){
    mat4 modelMat = mat4( 1., 0., 0., 0.,
                         0., 1., 0., 0.,
                         0., 0., 1., 0.,
                         0., 0., 0., 1. );
    _pos *= noiseScale;
    modelMat[0][0] += (snoise( vec3(time, _pos.y, _pos.z) )+1.)*0.5 * u_scale;
    modelMat[1][1] += (snoise( vec3(_pos.x, time, _pos.z) )+1.)*0.5 * u_scale;
    modelMat[2][2] += (snoise( vec3(_pos.x, _pos.y, time) )+1.)*0.5 * u_scale;
    return modelMat;
}



void main()
{
    // here we move the texture coordinates
    varyingtexcoord = vec2(texcoord.x, texcoord.y);
    vec4 pos = position;
    pos = scaleMat4(pos.xyz) * pos;
    
    // send the vertices to the fragment shader
    gl_Position = modelViewProjectionMatrix * pos;
    varyingPosition = pos;
    varyingNormal = normalize(transpose(inverse(scaleMat4(pos.xyz))) * normal);
}
