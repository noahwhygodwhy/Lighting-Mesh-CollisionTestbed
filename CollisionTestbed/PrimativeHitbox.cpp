#include "PrimativeHitbox.hpp"

PrimativeHitbox::PrimativeHitbox(vec3 origin, vec3 dims) : Hitbox(origin)
{
	this->dims = dims;
}

PrimativeHitbox::~PrimativeHitbox()
{
}
