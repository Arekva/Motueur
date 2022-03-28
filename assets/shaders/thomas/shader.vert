#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normals;

out vec2 UV;
out vec3 normal;
out vec3 light;
out vec3 pos;

uniform mat4 MVP;
uniform mat4 View;
uniform mat4 Model;
uniform vec3 LightWorld;
uniform mat4 lightSpaceMatrix;

void main(){
    
    gl_Position =   MVP * vec4(vertexPosition_modelspace,1);
    vec3 Position_worldspace = (Model * vec4(vertexPosition_modelspace,1)).xyz;  
    vec3 vertexPosition_cameraspace = ( View * Model * vec4(vertexPosition_modelspace,1)).xyz;
    vec3 lightPos = ( View * vec4(LightWorld.xyz,1)).xyz;
    light = lightPos - vertexPosition_cameraspace;
    UV = vertexUV;
    normal = (View*Model*vec4(normals,0)).xyz;

}