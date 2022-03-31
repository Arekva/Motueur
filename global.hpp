#pragma once

#include <GL/glew.h>

inline void check_ogl_error() {
#if _DEBUG
    do { if (glGetError() != GL_NONE) __debugbreak(); } while (false);
#endif
}