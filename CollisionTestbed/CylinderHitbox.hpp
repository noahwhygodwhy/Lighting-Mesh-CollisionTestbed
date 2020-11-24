#ifndef CYLINDER_HITBOX_H
#define CYLINDER_HITBOX_H

#include "Hitbox.hpp"


using namespace std;
using namespace glm;

class CylinderHitbox : public Hitbox
{
public:
	CylinderHitbox(vec3 origin, float radius, float height, HitboxType type = HitboxType::CYLINDER);
	~CylinderHitbox();
	float height;
	float radius;
	vec3 getMaxs();
	vec3 getMins();
private:

};

#endif