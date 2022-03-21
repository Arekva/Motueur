#pragma once
#include <GL/glew.h>
class Texture
{
public :

	GLuint ID;
	int width,height,bpp;

	Texture(const char* filename);

	~Texture();

    void Use(GLint unit) const;
};