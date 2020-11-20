#ifndef P_HITBOX_H
#define P_HITBOX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include "Hitbox.hpp"

using namespace std;
using namespace glm;

class PrimativeHitbox : public Hitbox
{
public:
	PrimativeHitbox(vec3 origin, vec3 dims);
	~PrimativeHitbox();

private:
	vec3 dims
};

#endif