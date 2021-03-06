#version 330 core
out vec3 color;
in vec2 UV;
in vec3 normal;
in vec3 pos;
in mat3 TBN;

uniform sampler2D Texture;
uniform sampler2D NMap;
uniform vec4 LightsColor[32];
uniform vec3 LightsWorld[32];
uniform mat4 View;
uniform int LightNbr;
uniform int nmapActive;

void main(){ 
    vec3 directional = normalize(vec3(1.0));

    vec3 n; 
    if(nmapActive==1)
    {
        vec3 tex_normal = normalize((texture(NMap, UV).rgb)*2.0 - 1.0);
        n = TBN*tex_normal;
    }
    else n = normalize(normal);

    vec3 recievedLight = vec3(0,0,0);

    for(int i =0; i<min(32,LightNbr);i++)
    {
        vec3 currlightPos = LightsWorld[i];
        vec3 currLight = currlightPos - pos;
        vec3 l = (View*vec4(normalize(currLight), 0)).xyz;
        float cosTheta = clamp( dot( n,l ),0,1);
        float  sqdist = pow(distance(currLight,pos), 2);
        recievedLight += (LightsColor[i].rgb * LightsColor[i].w / sqdist) * cosTheta; 
    }
    recievedLight += dot(n,(View*vec4(directional, 0.0)).xyz) * 1000.0;

    recievedLight += vec3(0.529, 0.808, 0.922) * 500.0;

    const vec3 GAMMA = vec3(1.0/2.2);
    const vec3 EXPOSURE = vec3(1.0/1000.0);
    vec3 light = texture( Texture, UV ).rgb*(max(recievedLight,70));
    vec3 raw_mapped = vec3(1.0) - exp(-light * EXPOSURE);
    color = raw_mapped;
}