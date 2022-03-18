#pragma once
#include <GL/glew.h>
class Texture
{
public :

	GLuint ID;
	int width,height,bpp;

	Texture(char* filename);

	~Texture();
};