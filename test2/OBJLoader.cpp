#include "OBJLoader.h"
#include <sstream>

struct Texture {
	unsigned int id;
	string type;
};
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

void OBJLoader::processVertex(std::vector<string> vertexData, std::vector<int> &indices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, float textureArray[], float normalsArray[])
{
	int currentVertexPointer = std::stoi(vertexData[0], 0) - 1;
	indices.push_back(currentVertexPointer);
	glm::vec2 currentTex = textures[std::stoi(vertexData[1], 0) - 1];
	textureArray[currentVertexPointer * 2] = currentTex.x;
	textureArray[currentVertexPointer * 2+1] = 1 - currentTex.y;
	glm::vec3 currentNorm = normals[std::stoi(vertexData[2], 0) - 1];
	normalsArray[currentVertexPointer * 3] = currentNorm.x;
	normalsArray[currentVertexPointer * 3 + 1] = currentNorm.y;
	normalsArray[currentVertexPointer * 3 + 2] = currentNorm.z;
}



/*

RawModel * OBJLoader::loadObjModel2(string fname, Loader loader)
{

	
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fname, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return new RawModel(31,1);
	}

	aiMesh* a = scene->mMeshes[0];

	vector<Vertex> vertices;
	vector<int> indices;
	vector<Texture> textures;
	
	for (int i = 0; i < a->mNumVertices; i++)
	{
		
	
		Vertex vertex;
		
		
		glm::vec3 temp;
		temp.x = a->mVertices[i].x;
		temp.y = a->mVertices[i].y;
		temp.z = a->mVertices[i].z;
		
		vertex.Position = temp;
		
		temp.x = a->mNormals[i].x;
		temp.y = a->mNormals[i].y;
		temp.z = a->mNormals[i].z;
		vertex.Normal = temp;

		if (a->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = a->mTextureCoords[0][i].x;
			vec.y = a->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);

		

	}
	
	for (unsigned int i = 0; i < a->mNumFaces; i++)
	{
		aiFace face = a->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	float* ver = new float[vertices.size() * 3];
	float* tex = new float[vertices.size() * 2];
	int* ind = new int[vertices.size()];
	std::vector<glm::vec3> tempVer;
	std::vector<glm::vec2> tempTex;
	
	for (int i = 0; i < vertices.size() ; i ++)
	{
		tempVer.push_back(vertices[i].Position);
		tempTex.push_back(vertices[i].TexCoords);
	}
	
	ind = &indices[0];
	ver = &tempVer[0].x;
	tex = &tempTex[0].x;

	return loader.loadToVAO(ver, vertices.size() * 3, tex, vertices.size() * 2, ver, vertices.size() * 3, ind, vertices.size());
}
*/




RawModel * OBJLoader::loadObjModel(string fname, Loader loader)
{
	int buf_size = 1024;
	std::ifstream vertexFile(fname);
	

	char* line = new char[buf_size];
	
	char* number = new char[10];
	
	vertexFile.getline(number, 10);
		int verAmount = atoi(number);
		int* indices = new int[verAmount];
		float* vertices = new float[verAmount * 3];
		float* textures = new float[verAmount * 2];
		float* normals = new float[verAmount * 3];
		int v = 0, t = 0, n = 0;
		for (int i = 0; i < verAmount; i++)
		{
			vertexFile.getline(line, buf_size);
			sscanf_s(line, "%f" "%f" "%f" "%f" "%f" "%f" "%f" "%f", &vertices[v], &vertices[v+1], &vertices[v+2], &textures[t], &textures[t+1] , &normals[n], &normals[n + 1], &normals[n + 2]);
			v += 3;
			n += 3;
			t += 2;
		}
		buf_size = 20;
		for (int i = 0; i < verAmount; i++)
		{
			indices[i] = i;
		}
		vertexFile.close();
		

		return loader.loadToVAO(vertices, verAmount * 3, textures, verAmount * 2, normals, verAmount * 3, indices, verAmount);
}

