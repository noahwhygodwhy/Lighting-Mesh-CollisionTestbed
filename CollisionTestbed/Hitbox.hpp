#ifndef HITBOX_H
#define HITBOX_H

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>


using namespace std;
using namespace glm;
using namespace nlohmann;

class Hitbox
{
public:
	//constructor for cubes/cylinders, spheres, and basic shapes like that
	Hitbox(vec3 origin);
	Hitbox();
	~Hitbox();

private:
	vec3 origin;
};

vec3 jsonToVec3(json j);
Hitbox jsonToHitbox(json j);

#endif