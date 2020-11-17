#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.hpp"
#include "Shader.hpp"
#include <vector>
#include "Model.hpp"
#include "Mesh.hpp"
#include "Thing.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include "Agent.hpp"

class Renderer
{
public:
	Renderer(int x, int  y);
	~Renderer();
	bool initialize();
	void run();
	void addThing(Thing* th);
	void setPlayer(Agent* p);
private:
	Agent* player;
	vector<IThing*> things;
	unsigned int largeTextureStack = 0;
	int screenX;
	int screenY;
	Camera cam;
	Shader shader;
	GLFWwindow* window;
	unsigned int VBO, VAO, EBO;
	int32_t layerCount;
};



#endif