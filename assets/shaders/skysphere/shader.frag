#version 330 core
out vec3 color;

in vec3 normal;

void main()
{
	vec3 bottom = vec3(0,0,150/255);
	vec3 top = vec3(150/255,200/255,1);
	
	color = mix(top,bottom,normal.y);
}