#pragma once

#include "image.hpp"
#include "cursor_icon.hpp"

class Cursor { };

class CursorInstance : Cursor {
private:
	Cursor* cursor;
public:
CursorInstance(const Image* image, 
			   int xhot, int yhot)
{
	this->cursor = reinterpret_cast<Cursor*>(glfwCreateCursor(reinterpret_cast<const GLFWimage*>(image), xhot, yhot));
}

CursorInstance(CursorIcon shape)
{
	this->cursor = reinterpret_cast<Cursor*>(glfwCreateStandardCursor(static_cast<int>(shape)));
}

~CursorInstance()
{
	glfwDestroyCursor(reinterpret_cast<GLFWcursor*>(this->cursor));
}

/* API EXTENSIONS */
Cursor* GetAPI()
{
	return cursor;
}

};

#undef RECAST