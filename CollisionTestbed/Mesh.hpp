#pragma once

#include <vector>
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad.h"
#include <GLFW/glfw3.h>

#include "Shader.hpp"

using namespace std;
using namespace glm;

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 texCoords;
};

struct Texture {
	unsigned int id;
	string type;
};

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader& shader);
	~Mesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

Mesh::~Mesh()
{
}
