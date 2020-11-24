#ifndef RECT_HITBOX_H
#define RECT_HITBOX_H

#include "Hitbox.hpp"

class CuboidHitbox : public Hitbox
{
public:
	CuboidHitbox(vec3 origin, vec3 dims, HitboxType type = HitboxType::CUBOID);
	~CuboidHitbox();
	vec3 otherCorner;
	vec3 getMaxs();
	vec3 getMins();
private:

};
#endif