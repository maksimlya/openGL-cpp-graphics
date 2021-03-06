#pragma once
#include "Loader.h"

class OBJLoader
{
private:
	static void processVertex(std::vector<string> , std::vector<int> &, std::vector<glm::vec2>, std::vector<glm::vec3>, float[] , float[]);

public: 
	static RawModel* loadObjModel(string fname, Loader loader);
	RawModel * OBJLoader::loadObjModel2(string fname, Loader loader);
};