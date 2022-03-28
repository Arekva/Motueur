#pragma once

#include <../../assimp/include/assimp/Importer.hpp>
#include <../../assimp/include/assimp/scene.h>
#include <../../assimp/include/assimp/postprocess.h>
#include <vector>

#include <glm/glm.hpp>
#include <iostream>
using namespace std;

class LoadModel
{

  public:
      ///*  Fonctions   */
      static bool loadModel(
          const char* path,
          vector<unsigned short>& indices,
          vector<glm::vec3>& vertices,
          vector<glm::vec2>& uvs,
          vector<glm::vec3>& normals

      );

  private:

      ///*  Donn�es du mod�le  */
      

     

      


};