#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.hpp"
#include "Shader.hpp"


#include "glad.h"
#include <GLFW/glfw3.h>

class Renderer
{
public:
	Renderer(int x, int  y);
	~Renderer();
	bool initialize();
private:

	unsigned int largeTextureStack = 0;
	int screenX;
	int screenY;
	Camera cam;
	Shader shader;
	GLFWwindow* window;
	unsigned int VBO, VAO, EBO;
	int32_t layerCount;
};



#endif // !RENDERER_H