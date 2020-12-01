#include "Light.hpp"
#include "glad.h"

Light::Light()
{
	setupLight();
}

Light::~Light()
{
}


void Light::setupLight()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}