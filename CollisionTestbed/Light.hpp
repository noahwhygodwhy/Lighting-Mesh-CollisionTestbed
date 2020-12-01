#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class Light
{
public:
	Light();
	~Light();

private:
	unsigned int VAO, VBO;
	void setupLight();
	vec3 position;
};
#endif;