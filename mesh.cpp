#include "GL/glew.h"

#include "mesh.hpp"
#include <../../assimp/include/assimp/Importer.hpp>
#include <../../assimp/include/assimp/scene.h>
#include <../../assimp/include/assimp/postprocess.h>

#include <iostream>

using namespace Motueur;

void Mesh::init() {  }
void Mesh::terminate() { }

inline GLuint Mesh::get_vertex_buffer()    { return _bufferObjects[0]; }
inline GLuint Mesh::get_index_buffer()     { return _bufferObjects[1]; }
inline GLuint Mesh::get_vertex_array()     { return _bufferObjects[2]; }

void Mesh::create_from_data(const Vertex* vertices, size_t vertex_count, const unsigned short* indices, size_t index_count) {
    _indexType = GL_UNSIGNED_SHORT; // todo: type de donnée custom avec template

    _vertexCount = vertex_count;
    _indexCount  = index_count ;

    int buffers_count = index_count == 0 ? 1 : 2;


    glGenVertexArrays(1, &_bufferObjects[2]);
    glBindVertexArray(get_vertex_array());

    // 0 - Vertex
    // 1 - Index
    // 3- VAO
    glGenBuffers(buffers_count, _bufferObjects);

    // remplissage des vertices
    glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count, vertices, GL_STATIC_DRAW);

    if (index_count)
    {
        // remplissage des indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, get_index_buffer());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * index_count, indices, GL_STATIC_DRAW);
    }

    /* position */
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));

    /* uv       */
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, uv      ));

    /* normal   */
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, normal  ));

    /* tangents */
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    /* bitangents */
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
}

Mesh::Mesh(const Vertex* vertices, size_t vertex_count, const unsigned short* indices, size_t index_count) {
    this->create_from_data(vertices, vertex_count, indices, index_count);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned short>& indices) {
    this->create_from_data(vertices.data(), vertices.size(),
         indices.data(), indices.size());
}

Mesh::Mesh(const char *path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_FlipUVs |
                                             aiProcess_CalcTangentSpace);
    if (!scene) {
        fprintf(stderr, importer.GetErrorString());
        getchar();
        return;
        //return false;
    }
    const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

    size_t vertex_count = mesh->mNumVertices;
    std::vector<Vertex> vertices;
    vertices.reserve(vertex_count);
    for (unsigned int i = 0; i < vertex_count; i++) {
        aiVector3D pos = mesh->mVertices[i];
        aiVector3D uv  = mesh->mTextureCoords[0][i];
        aiVector3D normal = mesh->mNormals[i];
        aiVector3D tangent = mesh->mTangents[i];
        aiVector3D bitangent = mesh->mBitangents[i];

        Vertex vert = {
            .position = glm::vec3(pos.x, pos.y, pos.z),
            .uv       = glm::vec2(uv.x, uv.y),
            .normal   = glm::vec3(normal.x, normal.y, normal.z),
            .tangent  = glm::vec3(tangent.x, tangent.y, tangent.z),
            .bitangent= glm::vec3(bitangent.x, bitangent.y, bitangent.z),
        };
        vertices.push_back(vert);
    }

    size_t face_count = mesh->mNumFaces;
    size_t index_count = face_count * 3;
    std::vector<unsigned short> indices;
    indices.reserve(index_count);
    for (unsigned int i = 0; i < face_count; i++) {
        indices.push_back(mesh->mFaces[i].mIndices[0]);
        indices.push_back(mesh->mFaces[i].mIndices[1]);
        indices.push_back(mesh->mFaces[i].mIndices[2]);
    }

    create_from_data(vertices.data(), vertex_count, indices.data(), index_count);
}


Mesh::~Mesh() {
    int buffers_count = _indexCount == 0 ? 1 : 2;

    glDeleteBuffers(buffers_count, _bufferObjects);
    glDeleteVertexArrays(1, &_bufferObjects[2]);
}

void Mesh::use() {
    glBindVertexArray(get_vertex_array());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
}

void Mesh::draw() {
    if (!_indexCount) { glDrawArrays(GL_TRIANGLES, 0, _vertexCount); }
    else { glDrawElements(GL_TRIANGLES, _indexCount, _indexType, (void*)0); }
}

void Mesh::draw_instancied(GLuint transform_buffer, size_t transform_count) {
    // bind to "transforms"
    // todo
}
