#include "skysphere.hpp"

#include <ctime>
#include <windows.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>

using namespace std;

#include <gl/glew.h>
#include <glm/glm.hpp>



void SkySphere::loadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom)
{
	//converson string to char 
	std::string Front = a_sDirectory + a_sFront;
	const char* FrontTexture = Front.c_str();

	std::string Back = a_sDirectory + a_sBack;
	const char* BackTexture = Back.c_str();

	std::string Left = a_sDirectory + a_sLeft;
	const char* LeftTexture = Left.c_str();

	std::string Right = a_sDirectory + a_sRight;
	const char* RightTexture = Right.c_str();

	std::string Top = a_sDirectory + a_sTop;
	const char* TopTexture = Top.c_str();

	std::string Bottom = a_sDirectory + a_sBottom;
	const char* BottomTexture = Bottom.c_str();



	tTextures[0] = Texture(FrontTexture);
	tTextures[1] = Texture(BackTexture);
	tTextures[2] = Texture(LeftTexture);
	tTextures[3] = Texture(RightTexture);
	tTextures[4] = Texture(TopTexture);
	tTextures[5] = Texture(BottomTexture);

	sDirectory = a_sDirectory;

	sFront = a_sFront;
	sBack = a_sBack;
	sLeft = a_sLeft;
	sRight = a_sRight;
	sTop = a_sTop;
	sBottom = a_sBottom;

	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);

	//vboRenderData.CreateVBO();
	//vboRenderData.BindVBO();

	glm::vec3 vSkyBoxVertices[24] =
	{
		// Front face
		glm::vec3(200.0f, 200.0f, 200.0f), glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(-200.0f, 200.0f, 200.0f), glm::vec3(-200.0f, -200.0f, 200.0f),
		// Back face
		glm::vec3(-200.0f, 200.0f, -200.0f), glm::vec3(-200.0f, -200.0f, -200.0f), glm::vec3(200.0f, 200.0f, -200.0f), glm::vec3(200.0f, -200.0f, -200.0f),
		// Left face
		glm::vec3(-200.0f, 200.0f, 200.0f), glm::vec3(-200.0f, -200.0f, 200.0f), glm::vec3(-200.0f, 200.0f, -200.0f), glm::vec3(-200.0f, -200.0f, -200.0f),
		// Right face
		glm::vec3(200.0f, 200.0f, -200.0f), glm::vec3(200.0f, -200.0f, -200.0f), glm::vec3(200.0f, 200.0f, 200.0f), glm::vec3(200.0f, -200.0f, 200.0f),
		// Top face
		glm::vec3(-200.0f, 200.0f, -200.0f), glm::vec3(200.0f, 200.0f, -200.0f), glm::vec3(-200.0f, 200.0f, 200.0f), glm::vec3(200.0f, 200.0f, 200.0f),
		// Bottom face
		glm::vec3(200.0f, -200.0f, -200.0f), glm::vec3(-200.0f, -200.0f, -200.0f), glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(-200.0f, -200.0f, 200.0f),
	};
	glm::vec2 vSkyBoxTexCoords[4] =
	{
		glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
	};

	glm::vec3 vSkyBoxNormals[6] =
	{
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};

	for(int q = 0;q < 24;q++)
	{
		//vboRenderData.AddData(&vSkyBoxVertices[q], sizeof(glm::vec3));
		//vboRenderData.AddData(&vSkyBoxTexCoords[q % 4], sizeof(glm::vec2));
		//vboRenderData.AddData(&vSkyBoxNormals[q / 4], sizeof(glm::vec3));
	}

	//vboRenderData.UploadDataToGPU(GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}



void SkySphere::renderSkybox()
{
	glDepthMask(0);
	glBindVertexArray(uiVAO);
	for (int i = 0; i < 6; i++)
	{
		//tTextures[i].bindTexture();
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	glDepthMask(1);
}


void SkySphere::DeleteSkybox()
{
	for(int i= 0;i<6;i++)
	{
		//tTextures[i].DeleteTexture();
		//glDeleteVertexArrays(1, &uiVAO);
		//vboRenderData.DeleteVBO();
	}
}