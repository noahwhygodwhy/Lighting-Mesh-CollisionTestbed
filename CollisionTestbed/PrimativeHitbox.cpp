#include "PrimativeHitbox.hpp"

PrimativeHitbox::PrimativeHitbox(vec3 origin, float dim1, float dim2, float dim3) : Hitbox(origin)
{
	this->dim1 = dim1;
	this->dim2 = dim2;
	this->dim3 = dim3;
}

PrimativeHitbox::~PrimativeHitbox()
{
}
