#include "PlllppHitbox.hpp"


PlllppHitbox::PlllppHitbox(vec3 origin, vec3 a, vec3 b, vec3 c) : Hitbox(origin)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

PlllppHitbox::~PlllppHitbox()
{
}