#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normals;

out vec2 UV;
out vec3 normal;
out vec3 light[32];
out vec3 pos;

uniform mat4 MVP;
uniform mat4 View;
uniform mat4 Model;
uniform vec3 LightWorld;
uniform int lightNbr;

//vec3 LightWorld;


void main(){
    gl_Position =   MVP * vec4(vertexPosition_modelspace,1);
    vec3 Position_worldspace = (Model * vec4(vertexPosition_modelspace,1)).xyz;  
    vec3 vertexPosition_cameraspace = ( View * Model * vec4(vertexPosition_modelspace,1)).xyz;
/*  for(int i = 0; i<lightNbr;i++ ){
        LightWorld = LightsWorld[i]; 
        vec3 lightPos = ( View * vec4(LightWorld.xyz,1)).xyz;
        light[i] = lightPos - vertexPosition_cameraspace;
    
    }LightWorld = LightsWorld[0]; */
        vec3 lightPos = ( View * vec4(LightWorld.xyz,1)).xyz;
        light[0] = lightPos - vertexPosition_cameraspace;
    UV = vertexUV;
    normal = (View*Model*vec4(normals,0)).xyz;
}