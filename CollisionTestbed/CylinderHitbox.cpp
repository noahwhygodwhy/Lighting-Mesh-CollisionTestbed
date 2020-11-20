#include "CylinderHitbox.hpp"

CylinderHitbox::CylinderHitbox(vec3 origin, float radius, float height) : Hitbox(origin)
{
	this->radius = radius;
	this->height = height;
}

CylinderHitbox::~CylinderHitbox()
{
}