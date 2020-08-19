#pragma once

#include "Model.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//NEVER USE
Model::Model()
{
	//TODO: load a default model to indicate errors?
}

Model::Model(char* path)
{
	stbi_set_flip_vertically_on_load(true);
	loadModel(path);
}

Model::~Model()
{
}

void Model::draw(Shader& shader)
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].draw(shader);
	}
}

void Model::loadModel(string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);//maybe do aiProcess_OptimizeMeshes?
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR IN ASSIMP, MODEL.CPP LoadModel()\n" << import.GetErrorString() << endl;
		exit(-1);
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}




unsigned int TextureFromFile(const char* fileName, const string directory)
{

	string path = string(fileName);
	path = directory + '/' + fileName;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, channels;

	unsigned char* initImage = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (initImage)
	{
		GLenum format;
		switch (channels)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4: 
			format = GL_RGBA;
			break;
		default:
			printf("DEFAULT? WHAT THE FUCK IS GOING ON?\n\n\n\n\n\n\n\n\n");
			break;
		}
		
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, initImage);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(initImage);
	}
	else
	{
		fprintf(stderr, "image not loaded\n");
		fprintf(stderr, "%s\n", path.c_str());
		stbi_image_free(initImage);
		exit(-1);
	}
	return textureID;
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (size_t i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;

		for (size_t j = 0; j < loadedTextures.size(); j++)
		{
			if (strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}
	return textures;
}


Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;
		v.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		//printf("vertex:\t %f\t %f\t %f\t", v.position.x, v.position.y, v.position.z);
		v.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
		{
			v.texCoords = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			v.texCoords = vec2(0.0f, 0.0f);
		}
		//printf("uvs:\t %f\t %f\n", v.texCoords.x, v.texCoords.y);
		vertices.push_back(v);
	}
	for (size_t i = 0; i < mesh->mNumFaces; i++)//for each face
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)//for each indice in that face
		{
			indices.push_back(face.mIndices[j]);//get it
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}