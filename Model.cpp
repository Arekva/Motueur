#include "Model.hpp"



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;


//void Draw(Shader shader)
//{
//    for (unsigned int i = 0; i < meshes.size(); i++)
//        meshes[i].Draw(shader);
//}

bool LoadModel::loadModel(const char* path, vector<unsigned short>& indices, vector<glm::vec3>& vertices, vector<glm::vec2>& uvs, vector<glm::vec3>& normals, vector<glm::vec3>& tangent, vector<glm::vec3>& bitangent)
{
    
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene) {
        fprintf(stderr, importer.GetErrorString());
        getchar();
        return false;
    }
    const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

    // Fill vertices positions
    vertices.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D pos = mesh->mVertices[i];
        vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
    }

    // Fill vertices texture coordinates
    uvs.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
        uvs.push_back(glm::vec2(UVW.x, UVW.y));
    }

    // Fill vertices normals
    normals.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D n = mesh->mNormals[i];
        normals.push_back(glm::vec3(n.x, n.y, n.z));
    }

    // Fill vertices tangents
    tangent.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D n = mesh->mTangents[i];
        tangent.push_back(glm::vec3(n.x, n.y, n.z));
    }

    // Fill vertices bitangents
    bitangent.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D n = mesh->mBitangents[i];
        bitangent.push_back(glm::vec3(n.x, n.y, n.z));
    }

    // Fill face indices
    indices.reserve(3 * mesh->mNumFaces);
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        // Assume the model has only triangles.
        indices.push_back(mesh->mFaces[i].mIndices[0]);
        indices.push_back(mesh->mFaces[i].mIndices[1]);
        indices.push_back(mesh->mFaces[i].mIndices[2]);
    }

// The "scene" pointer will be deleted automatically by "importer"
    return true;
}


