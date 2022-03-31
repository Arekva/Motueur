#version 450
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normals;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec2 UV;
out vec3 normal;
out vec3 pos;
out mat3 TBN;

uniform mat4 View;
uniform mat4 Model;
uniform mat4 Projection;

uniform vec3 LightsWorld[32];
uniform vec4 LightsColor[32];
uniform int LightNbr;


uniform int IsInstanced;
layout (std430, binding=10) buffer InstanceBuffer
{
    mat4 models[];
};

void main() {
    mat4 model;
    if (IsInstanced == 1) {
        model = models[gl_InstanceID];
    }
    else {
        model = Model;
    }


    gl_Position = Projection * View * model * vec4(vertexPosition_modelspace,1);
    vec3 Position_worldspace = (model * vec4(vertexPosition_modelspace,1)).xyz;  
    vec3 vertexPosition_cameraspace = ( View * model * vec4(vertexPosition_modelspace,1)).xyz;
    mat3 MV = mat3(View * model);

    vec3 normalsCam = MV * normalize(normals); 
    vec3 tangentCam = MV * normalize(tangent); 
    vec3 bitangentCam = MV * normalize(bitangent); 
    TBN = mat3( tangentCam, bitangentCam, normalsCam);
    pos = (model * vec4(vertexPosition_modelspace, 1.0)).xyz;
    UV = vertexUV;
    normal = (View*model*vec4(normals,0)).xyz;
}