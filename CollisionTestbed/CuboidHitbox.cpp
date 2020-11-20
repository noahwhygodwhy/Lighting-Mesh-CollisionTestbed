#include "CuboidHitbox.hpp"


CuboidHitbox::CuboidHitbox(vec3 origin, vec3 otherCorner) : Hitbox(origin)
{
	this->otherCorner = otherCorner;
}

CuboidHitbox::~CuboidHitbox()
{

}