#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Shader.hpp"
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>

using namespace std;



class Model
{
public:
	Model();
	Model(const char* path);
	~Model();
	void draw(Shader& shader, glm::mat4 transform);
	string directory;
private:
	vector<Texture> loadedTextures;
	vector<Mesh> meshes;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	vector<vector<Vertex>*> getVectors();
};

#endif // !MODEL_H