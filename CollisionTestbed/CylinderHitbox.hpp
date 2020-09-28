#ifndef CYLINDER_HITBOX_H
#define CYLINDER_HITBOX_H

#include "PrimativeHitbox.hpp"


using namespace std;
using namespace glm;

class CylinderHitbox : PrimativeHitbox
{
public:
	CylinderHitbox(vec3 origin, float radius, float height);
	~CylinderHitbox();

private:

};

#endif