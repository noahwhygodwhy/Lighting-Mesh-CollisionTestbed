#ifndef CYLINDER_HITBOX_H
#define CYLINDER_HITBOX_H

#include "Hitbox.hpp"


using namespace std;
using namespace glm;

class CylinderHitbox : public Hitbox
{
public:
	CylinderHitbox(vec3 origin, float radius, float height);
	~CylinderHitbox();
	float height;
	float radius;
private:

};

#endif