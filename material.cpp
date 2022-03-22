#include "material.hpp"

namespace Motueur {



Material::Material(std::shared_ptr<Shader> shader) {
    GLint uniform_count;
    std::unordered_map<std::string, ShaderUniformData>* uniforms = shader->get_bindings(&uniform_count);

    _data_memory = malloc(256 * uniform_count);

    _data.reserve(uniform_count);

    int i = 0;
    for (const auto& uniform: *uniforms) {
        MaterialData data = {
            .Uniform = uniform.second,
            .Setter  = setters.at(uniform.second.Type),
            .Data    = (char*)_data_memory + 256 * i
        };
        _data.insert({uniform.first, data});
        ++i;
    }
    _shader = std::move(shader);
}

Material::~Material() {
    free(_data_memory);
}

void Material::Use() {
    _textureIndex = 0;

    for (const auto& uniform: _data) {
        MaterialData data = uniform.second;
        if (data.Data != nullptr) { // update uniforms
            data.Setter(this, data.Uniform.Location, data.Data);

            if (data.Uniform.Type == GL_SAMPLER_2D) {
                ++_textureIndex;
            }
        }
    }
}

}