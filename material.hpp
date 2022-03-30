#pragma once

#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "shader.hpp"
#include "texture.hpp"

namespace Motueur {

    class Material;

    typedef void (*UniformSetter)(Material* material, GLint location, int count, void* data);

    struct MaterialData {
        ShaderUniformData Uniform;
        UniformSetter     Setter ;
        int               Count  ;
        void*             Data   ;
    };

}

inline void check_ogl_error() {
#if _DEBUG
    do { if (glGetError() != GL_NONE) __debugbreak(); } while (false);
#endif
}

namespace Motueur {

    class Material {
    private:


        const std::unordered_map<GLenum, UniformSetter> setters =
        {
        { GL_INT       , [] (Material* material, GLint location, int count, void* data) -> void {
            glUniform1i       (location, *(int*)data  );
            check_ogl_error();
        }},
        { GL_FLOAT     , [] (Material* material, GLint location, int count, void* data) -> void {
            glUniform1f       (location, *(float*)data);
            check_ogl_error();
        }},
        { GL_FLOAT_MAT4, [] (Material* material, GLint location, int count, void* data) -> void {
            glUniformMatrix4fv(location, count, false, glm::value_ptr(*(glm::mat4*)data));
            check_ogl_error();
        }},
        { GL_FLOAT_VEC3, [] (Material* material, GLint location, int count, void* data) -> void {
            glUniform3fv      (location, count, (float*)data);
            check_ogl_error();
        }},
        { GL_SAMPLER_2D, [] (Material* material, GLint location, int count, void* data) -> void {
            const int index = material->_textureIndex;

            ((Texture*)data)->Use(GL_TEXTURE0 + index);
            glUniform1i(location, index);
            check_ogl_error();
        }},
        { GL_FLOAT_VEC4, [] (Material* material, GLint location, int count, void* data) -> void {
            
            glUniform4fv      (location, count, (float*)data);
            check_ogl_error();
        }},
        };

        std::shared_ptr<Shader>                       _shader;
        std::unordered_map<std::string, MaterialData> _data  ;
        int                                           _textureIndex;
        void*                                         _data_memory;
        int                                           _id;

        static int                                    _currentId;

    public :
        Material(std::shared_ptr<Shader> shader);
        ~Material();

        void use();

        template<class T>
        void set_data(const char* name, const T* data, int count) {
            if (_data.find(name) != _data.end()) {
                MaterialData* mat_data = &_data.at(name);

                memcpy(mat_data->Data, data, sizeof(T) * count);
                mat_data->Count = count;

                if (_currentId == _id) { // directly set if current material is being used.
                    mat_data->Setter(this, mat_data->Uniform.Location, count, mat_data->Data);
                }
            }
            else {
                std::cout << "Material uniform \"" << name << "\" do not exist or is not active in the shader program.";
            }
        }

        template<class T>
        void set_data(const char* name, const T* data) {
            set_data<T>(name, data, 1);
        }
    };

}