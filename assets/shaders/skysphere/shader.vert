#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normals;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec3 normal; 

uniform mat4 View;
uniform mat4 Projection;



void main(){   
    gl_Position =  Projection * View * vec4(vertexPosition_modelspace,1);
    normal = normals;
}