#pragma once

#include <vector>
#include "vertex.hpp"

namespace Motueur {

class Mesh {
private:
    static GLuint _vaos[1]; // VAO = Vertex Attribute Object

    static inline GLuint get_standard_vao();
    static void create_vaos();



    GLuint _bufferObjects[2];

    inline GLuint get_vertex_buffer();
    inline GLuint get_index_buffer();

    GLenum _indexType;

    void create_from_data(const Vertex* vertices, size_t vertex_count, const unsigned int* indices, size_t index_count);
public:
    static void init();
    static void terminate();


    Mesh(const Vertex* vertices, size_t vertex_count, const unsigned int* indices, size_t index_count);
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    Mesh(const char* path);

    ~Mesh();

    void Draw(GLuint transform_buffer, size_t transform_count);
};

} // namespace Motueur