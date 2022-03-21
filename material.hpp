#pragma once

#include <memory>
#include <unordered_map>
#include "shader.hpp"

namespace Motueur {

class Material;

typedef void (*UniformSetter)(Material* material, GLint location, void* data);

struct MaterialData {
    ShaderUniformData Uniform;
    UniformSetter     Setter ;
    void*             Data   ;
};

}

namespace Motueur {

class Material {
private:


    const std::unordered_map<GLenum, UniformSetter> setters =
    {
        // 1D
    { GL_INT       , [] (Material* material, GLint location, void* data) -> void { glUniform1i       (location, *(int*)data  );           }},
    { GL_FLOAT     , [] (Material* material, GLint location, void* data) -> void { glUniform1f       (location, *(float*)data);           }},
    { GL_FLOAT_MAT4, [] (Material* material, GLint location, void* data) -> void { glUniformMatrix4fv(location, 1, false, (float*)data ); }},
    { GL_SAMPLER_2D, [] (Material* material, GLint location, void* data) -> void {
        const int index = material->_textureIndex;

        // ((Texture*)data)->Use(GL_TEXTURE0 + index);
        glUniform1i(location, index);
    }}


        // 2D
    };

    std::shared_ptr<Shader>                       _shader;
    std::unordered_map<std::string, MaterialData> _data  ;
    int                                           _textureIndex;

public :
    Material(std::shared_ptr<Shader> shader);

    void Use();
};

}