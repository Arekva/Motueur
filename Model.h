

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include <glm/glm.hpp>
#include <iostream>
using namespace std;

class LoadModel
{

  public:
      ///*  Fonctions   */
      bool loadModel(
          const char* path,
          vector<unsigned short>& indices,
          vector<glm::vec3>& vertices,
          vector<glm::vec2>& uvs,
          vector<glm::vec3>& normals

      );

  private:

      ///*  Données du modèle  */
      

     

      


};