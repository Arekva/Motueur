#include "GL/glew.h"

#include "mesh.hpp"

using namespace Motueur;

GLuint Mesh::_vaos[1];

inline GLuint Mesh::get_standard_vao() { return _vaos[0]; }

void Mesh::init() { create_vaos(); }
void Mesh::terminate() { glDeleteVertexArrays(1, _vaos); }

void Mesh::create_vaos() {
    // création des vertex array buffers (en gros ce qui dis comment mettre les vertex dans le shader
    glCreateVertexArrays(1, _vaos);

    // définition des attributs standards du moteur:
    //  [0] position (vec3)
    //  [1] uv (vec2)
    //  [2] normal (vec3)
    //  [3] tangent (vec4)
    GLuint standard_vao_handle = get_standard_vao();
    glEnableVertexAttribArray(standard_vao_handle);

    /* position */ glVertexAttribPointer(0, sizeof(glm::vec3), GL_FLOAT, false, sizeof(Vertex),
                                         (void*)offsetof(Vertex, position));
    /* uv       */ glVertexAttribPointer(1, sizeof(glm::vec2), GL_FLOAT, false, sizeof(Vertex),
                                         (void*)offsetof(Vertex, uv      ));
    /* normal   */ glVertexAttribPointer(2, sizeof(glm::vec3), GL_FLOAT, false, sizeof(Vertex),
                                         (void*)offsetof(Vertex, normal  ));
    /* tangents */ glVertexAttribPointer(3, sizeof(glm::vec4), GL_FLOAT, false, sizeof(Vertex),
                                         (void*)offsetof(Vertex, tangent ));

    glDisableVertexAttribArray(standard_vao_handle);
}



inline GLuint Mesh::get_vertex_buffer()    { return _bufferObjects[0]; }
inline GLuint Mesh::get_index_buffer()     { return _bufferObjects[1]; }

void Mesh::create_from_data(const Vertex* vertices, size_t vertex_count, const unsigned int* indices, size_t index_count) {
    _indexType = GL_UNSIGNED_INT; // todo: type de donnée custom avec template

    // création du vertex buffer et de l'index buffer
    glGenBuffers(2, _bufferObjects);

    // remplissage des vertices
    glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count, vertices, GL_STATIC_DRAW);

    if (index_count != 0)
    {
        // remplissage des indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, get_index_buffer());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index_count, indices, GL_STATIC_DRAW);
    }

    _vertexCount = vertex_count;
    _indexCount  = index_count ;

}

Mesh::Mesh(const Vertex* vertices, size_t vertex_count, const unsigned int* indices, size_t index_count) {
    this->create_from_data(vertices, vertex_count, indices, index_count);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    this->create_from_data(vertices.data(), vertices.size() / sizeof(Vertex),
         indices.data(), indices.size() / sizeof(unsigned int));
}

Mesh::Mesh(const char *path) {

}


Mesh::~Mesh() {
    glDeleteBuffers(2, _bufferObjects);
}

void Mesh::draw() {
    if (!_indexCount){
        glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, get_index_buffer());
        glDrawElements(GL_TRIANGLES, _indexCount, _indexType, 0);
    }
}

void Mesh::draw_instancied(GLuint transform_buffer, size_t transform_count) {
    // bind to "transforms"
    // todo
}
