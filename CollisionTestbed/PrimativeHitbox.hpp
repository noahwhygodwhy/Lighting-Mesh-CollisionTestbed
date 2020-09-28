#ifndef P_HITBOX_H
#define P_HITBOX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include "Hitbox.hpp"

using namespace std;
using namespace glm;

class PrimativeHitbox : Hitbox
{
public:
	PrimativeHitbox(vec3 origin, float dim1, float dim2, float dim3);
	~PrimativeHitbox();

private:
	float dim1;
	float dim2;
	float dim3;
};

#endif