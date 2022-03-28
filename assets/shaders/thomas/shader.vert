#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normals;

out vec2 UV;
out vec3 normal;
out vec3 pos;

uniform mat4 MVP;
uniform mat4 View;
uniform mat4 Model;
uniform vec3 LightsWorld[32];
uniform vec4 LightsColor[32];
uniform int LightNbr;

void main(){    
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    vec3 Position_worldspace = (Model * vec4(vertexPosition_modelspace,1)).xyz;  
    vec3 vertexPosition_cameraspace = ( View * Model * vec4(vertexPosition_modelspace,1)).xyz;
    pos = (Model * vec4(vertexPosition_modelspace, 1.0)).xyz;
    UV = vertexUV;
    normal = (View*Model*vec4(normals,0)).xyz;
}