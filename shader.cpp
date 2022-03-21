#include "GL/glew.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>

#include <sys/stat.h>
#include <vector>

#include "shader.hpp"

struct ShaderInfo {
    const char* FileName    ;
    GLint       GLIdentifier;
};

const size_t SHADER_MAX_COUNT = 5;

namespace Motueur {

const ShaderInfo SHADER_INFOS[SHADER_MAX_COUNT] {
    { "shader.vert", GL_VERTEX_SHADER          },
    { "shader.tesc", GL_TESS_CONTROL_SHADER    },
    { "shader.tese", GL_TESS_EVALUATION_SHADER },
    { "shader.geom", GL_GEOMETRY_SHADER        },
    { "shader.frag", GL_FRAGMENT_SHADER        },
};

inline bool do_file_exists(const char* path) {
    FILE *file;
    if (file = fopen(path, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string read_file(const char* file_path) {

    std::ifstream t(file_path);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);
    t.close();
    return buffer;
}

void Shader::create_uniform_map() {
    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &_uniformCount);
    _uniforms.reserve(_uniformCount);

    for (int i = 0; i < _uniformCount; ++i) {
        GLint  size            ;
        GLchar name_buffer[256];
        GLint  uniform_size    ;
        GLenum type            ;
        glGetActiveUniform(_program, i, 256, &size, &uniform_size, &type, name_buffer);

        GLchar* name_raw = (GLchar*)malloc(sizeof(GLchar) * size);

        std::memcpy(name_raw, name_buffer, sizeof(GLchar) * size);
        std::string name(name_raw, size);

        ShaderUniformData data = {
            .Name     = name,
            .Location = i,
            .Size     = size,
            .Type     = type
        };
        _uniforms.insert({name, data});

        if(type == GL_SAMPLER_2D) {
            ++_textureCount;
        }
    }
}

Shader::Shader(const char *path) {
    _program = glCreateProgram();
    GLint modules[7];

    int shader_count = 0;
    for (int i = 0; i < SHADER_MAX_COUNT; ++i) {
        std::string file_path = std::string(path) + '/' + SHADER_INFOS[i].FileName;

        if (do_file_exists(file_path.c_str())) {
            GLuint module_handle
                = modules[shader_count]
                = glCreateShader(SHADER_INFOS[i].GLIdentifier);

            std::string source = read_file(file_path.c_str()).c_str();

            const char* c_src = source.c_str();
            const GLint length = source.length();

            glShaderSource(module_handle, 1, &c_src, &length);
            glCompileShader(module_handle);

            // get compilation log
            GLint result = GL_FALSE;
            glGetShaderiv(module_handle, GL_COMPILE_STATUS, &result);

            if (result == GL_FALSE)
            {
                int log_length;
                glGetShaderiv(module_handle, GL_INFO_LOG_LENGTH, &log_length);
                std::vector<char> error_text(std::max(log_length, 1));
                glGetShaderInfoLog(module_handle, log_length, nullptr, error_text.data());
                std::cout << error_text.data() << std::endl;
            }
            else
            {
                ++shader_count;
                glAttachShader(_program, module_handle);
            }
        }
    }

    glLinkProgram(_program);

    GLint status;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int log_length;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> error_text(std::max(log_length, 1));
        glGetProgramInfoLog(_program, log_length, nullptr, error_text.data());
        std::cout << error_text.data() << std::endl;
    }

    create_uniform_map();

    // cleanup
    for (int i = 0; i < shader_count; ++i) {
        glDetachShader(_program, modules[i]);
        glDeleteShader(modules[i]);
    }
}



Shader::~Shader() {
    glDeleteProgram(_program);
}

std::unordered_map<std::string, ShaderUniformData>* Shader::get_bindings(GLint* count) {
    *count = _uniformCount;
    return &_uniforms;
}

}