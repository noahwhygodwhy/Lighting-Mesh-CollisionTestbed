#pragma once

#include "Model.h"

Model::Model(char* path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(Shader& shader)
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}