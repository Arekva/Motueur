#pragma once

#include <vector>
#include <memory>
#include "vertex.hpp"

namespace Motueur {

class Material;

class Mesh {
private:
    GLuint _bufferObjects[3];

    inline GLuint get_vertex_buffer();
    inline GLuint get_index_buffer();
    inline GLuint get_vertex_array();

    GLenum _indexType;

    size_t _vertexCount;
    size_t _indexCount;

    void create_from_data(const Vertex* vertices, size_t vertex_count, const unsigned short* indices, size_t index_count);
public:
    static void init();
    static void terminate();


    Mesh(const Vertex* vertices, size_t vertex_count, const unsigned short* indices, size_t index_count);
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned short>& indices);
    Mesh(const char* path);

    ~Mesh();

    void use();
    void draw(std::shared_ptr<Material> material);
    void draw_instanced(std::shared_ptr<Material> material, GLuint transform_buffer, size_t transform_count);
};

} // namespace Motueur