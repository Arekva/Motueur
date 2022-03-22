#include "material.hpp"

namespace Motueur {



Material::Material(std::shared_ptr<Shader> shader) {
    GLint uniform_count;
    std::unordered_map<std::string, ShaderUniformData>* uniforms = shader->get_bindings(&uniform_count);
    _data.reserve(uniform_count);
    for (const auto& uniform: *uniforms) {
        MaterialData data = {
            .Uniform = uniform.second,
            .Setter  = setters.at(uniform.second.Type),
            .Data    = nullptr
        };
        _data.insert({uniform.first, data});
    }
    _shader = std::move(shader);
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

    template<typename T>
    void Material::SetData(const char *name, T *data) {
        _data.at(name).Data = data;
    }
}