#include "CuboidHitbox.hpp"


CuboidHitbox::CuboidHitbox(vec3 origin, vec3 otherCorner, HitboxType type) : Hitbox(origin, type)
{
	this->otherCorner = otherCorner;
}

CuboidHitbox::~CuboidHitbox()
{

}