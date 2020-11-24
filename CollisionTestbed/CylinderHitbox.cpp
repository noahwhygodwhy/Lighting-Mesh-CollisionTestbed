#include "CylinderHitbox.hpp"

CylinderHitbox::CylinderHitbox(vec3 origin, float radius, float height, HitboxType type) : Hitbox(origin, type)
{
	this->radius = radius;
	this->height = height;
}

CylinderHitbox::~CylinderHitbox()
{
}
vec3 CylinderHitbox::getMaxs()
{
	return vec3(origin.x + radius, origin.y+height, origin.z + radius);
}
vec3 CylinderHitbox::getMins()
{
	return vec3(origin.x - radius, origin.y, origin.z - radius);
}