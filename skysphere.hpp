#pragma once
#include "texture.hpp"
// Header files of frequent usage

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


class SkySphere {

public:
	
	void loadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom);
	void renderSkybox();
	void DeleteSkybox();

	void releaseSkybox();
private:
	UINT uiVAO;
	//CVertexBufferObject vboRenderData;
	Texture tTextures[6];
	string sDirectory;
	string sFront;
	string sBack;
	string sLeft;
	string sRight;
	string sTop;
	string sBottom;
};