#ifndef OBJECT_H
#define OBJECT_H

#include "Thing.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;

class Object : public Thing
{
public:
	Object(Model m, Hitbox h, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));
	~Object();

private:

};
#endif