#pragma once

#include "GL/glew.h"

#include <unordered_map>

namespace Motueur {

struct ShaderUniformData {
    std::string Name    ;
    GLint       Location;
    GLint       Size    ;
    GLenum      Type    ;
};

class Shader {
private:
    GLuint                                              _program     ;
    std::unordered_map<std::string, ShaderUniformData>  _uniforms    ;
    GLint                                               _uniformCount;
    GLint                                               _textureCount;

    void create_uniform_map();
public:
    explicit Shader(const char* path);
    ~Shader();

    std::unordered_map<std::string, ShaderUniformData>* get_bindings(GLint* count);
    void use();
    GLuint program();
};

}