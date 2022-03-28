#version 330 core
out vec3 color;
in vec2 UV;
in vec3 normal;
in vec3 light;
in vec3 pos;

uniform sampler2D myTextureSampler;
uniform vec4 LightColor;


void main(){
    vec3 l = normalize(light);
    vec3 n = normalize(normal);
    float cosTheta = clamp( dot( n,l ),0,1);

    float sqdist = pow(distance(light,pos), 2);

    color = texture( myTextureSampler, UV ).rgb*(max(cosTheta*pow(LightColor.a,0.5)/sqdist,0.1))*LightColor.rgb;

}