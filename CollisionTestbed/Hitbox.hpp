#ifndef HITBOX_H
#define HITBOX_H

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



using namespace std;
using namespace glm;

class Hitbox
{
public:
	//constructor for cubes/cylinders, spheres, and basic shapes like that
	Hitbox(vec3 origin);
	~Hitbox();

private:
	vec3 origin;
};

#endif