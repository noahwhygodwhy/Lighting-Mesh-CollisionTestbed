#ifndef SPHERE_HITBOX_H
#define SPHERE_HITBOX_H

#include "Hitbox.hpp"


using namespace std;
using namespace glm;

class SphereHitbox : public Hitbox
{
public:
	SphereHitbox(vec3 origin, float radius, HitboxType type = HitboxType::SPHERE);
	~SphereHitbox();
	float radius;
	vec3 getMaxs();
	vec3 getMins();
private:

};

#endif