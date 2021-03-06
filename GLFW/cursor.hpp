#pragma once

#include "image.hpp"
#include "cursor_icon.hpp"

class Cursor { };

class CursorInstance : Cursor {
private:
	Cursor* cursor;
public:
inline CursorInstance(const Image* image,int xhot, int yhot)
{
	this->cursor = reinterpret_cast<Cursor*>(glfwCreateCursor(reinterpret_cast<const GLFWimage*>(image), xhot, yhot));
}

inline CursorInstance(CursorIcon shape)
{
	this->cursor = reinterpret_cast<Cursor*>(glfwCreateStandardCursor(static_cast<int>(shape)));
}

inline ~CursorInstance()
{
	glfwDestroyCursor(reinterpret_cast<GLFWcursor*>(this->cursor));
}

/* API EXTENSIONS */
inline Cursor* GetAPI()
{
	return cursor;
}

};

#undef RECAST