#version 330 core
out vec3 color;
in vec2 UV;
in vec3 normal;
in vec3 pos;

uniform sampler2D myTextureSampler;
uniform vec4 LightsColor[32];
uniform vec3 LightsWorld[32];
uniform mat4 View;
uniform int LightNbr;

void main(){
    vec3 currlightPos;
    vec3 l;
    vec3 n = normalize(normal);
    float cosTheta;
    float sqdist;
    vec3 currLight;
    vec3 recievedLight = vec3(0,0,0);
    for(int i =0; i<min(32,LightNbr);i++){
        currlightPos = LightsWorld[i].xyz;
        currLight = currlightPos - pos;
        l = normalize(currLight);
        cosTheta = clamp( dot( n,l ),0,1);
        sqdist = pow(distance(currLight,pos), 2);
        recievedLight += (LightsColor[i].rgb * LightsColor[i].w / sqdist) * cosTheta;  
    }

    const vec3 GAMMA = vec3(1.0/2.2);
    const vec3 EXPOSURE = vec3(1.0/1000.0);

    vec3 light = texture( myTextureSampler, UV ).rgb*(max(recievedLight,0.1));

    vec3 raw_mapped = vec3(1.0) - exp(-light * EXPOSURE);

    //vec3 gamma_corrected = pow(raw_mapped, GAMMA);

    color = raw_mapped;
}