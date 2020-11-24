#include "CuboidHitbox.hpp"


CuboidHitbox::CuboidHitbox(vec3 origin, vec3 otherCorner, HitboxType type) : Hitbox(origin, type)
{
	this->otherCorner = otherCorner;
}

CuboidHitbox::~CuboidHitbox()
{

}
vec3 CuboidHitbox::getMaxs()
{
	return glm::max(origin, otherCorner);
}
vec3 CuboidHitbox::getMins()
{
	return glm::min(origin, otherCorner);
}