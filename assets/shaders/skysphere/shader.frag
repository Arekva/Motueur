#version 330 core
out vec3 color;

in vec3 normal;

void main()
{
	vec3 bottom = vec3(0,0,0);
	vec3 top = vec3(1,1,1);
	
	color = mix(top,bottom,normal.y);
}