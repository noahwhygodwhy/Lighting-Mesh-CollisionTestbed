#include "CylinderHitbox.hpp"

CylinderHitbox::CylinderHitbox(vec3 origin, float radius, float height, HitboxType type) : Hitbox(origin, type)
{
	this->radius = radius;
	this->height = height;
}

CylinderHitbox::~CylinderHitbox()
{
}