#version 330 core
out vec3 color;
in vec2 UV;
in vec3 normal;
in vec3 light;

uniform sampler2D myTextureSampler;
uniform vec3 LightColor;


void main(){
    vec3 l = normalize(light);
    //l = vec3(0,-1,0);
    vec3 n = normalize(normal);
    float cosTheta = clamp( dot( n,l ),0,1);

    color = texture( myTextureSampler, UV ).rgb*(max(cosTheta,0.1));
    
}