#version 330 core
out vec3 color;

in vec3 normal;

void main()
{
	vec3 bottom = vec3(1.0,1.0,1.0);
	vec3 top = vec3(0.529,0.808,0.922);
	
	float pct = (normal.y + 1.0) / 2.0;

	color = mix(top,bottom,pct);
}