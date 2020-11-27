#include "SphereHitbox.hpp"

SphereHitbox::SphereHitbox(vec3 origin, float radius, float height, HitboxType type) : Hitbox(origin, type)
{
	this->radius = radius;
}

SphereHitbox::~SphereHitbox()
{
}
vec3 SphereHitbox::getMaxs()
{
	return origin + vec3(radius);
}
vec3 SphereHitbox::getMins()
{
	return origin + vec3(-radius);
}