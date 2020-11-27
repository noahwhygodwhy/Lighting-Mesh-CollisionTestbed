#include "Hitbox.hpp"
#include "CylinderHitbox.hpp"
#include "CuboidHitbox.hpp"
Hitbox::Hitbox(vec3 origin, HitboxType type)
{
	this->type = type;
	this->origin = origin;
}

Hitbox::Hitbox()
{
	this->type = HitboxType::PLAIN;
	this->origin = vec3(0);
}

vec3 Hitbox::getMaxs()
{	
	if (this->type == HitboxType::CUBOID)
		return ((CuboidHitbox*)this)->getMaxs();
	if (this->type == HitboxType::CYLINDER)
		return ((CylinderHitbox*)this)->getMaxs();

	return this->origin;
}
vec3 Hitbox::getMins()
{
	if (this->type == HitboxType::CUBOID)
		return ((CuboidHitbox*)this)->getMins();
	if (this->type == HitboxType::CYLINDER)
		return ((CylinderHitbox*)this)->getMins();
	return this->origin;
}

Hitbox::~Hitbox()
{
}

vec3 jsonToVec3(json j)
{
	return vec3(j["x"], j["y"], j["z"]);
}
Hitbox* jsonToHitbox(json j)
{
	string type = j["type"];
	if (type == "cylinder")
	{
		float radius = j["radius"];
		float height = j["height"];
		vec3 origin = jsonToVec3(j["origin"]);
		return new CylinderHitbox(origin, radius, height);
	}
	if (type == "cuboid")
	{
		vec3 origin = jsonToVec3(j["origin"]);
		vec3 dims = jsonToVec3(j["dims"]);
		vec3 otherCorner = origin + dims;
		return new CuboidHitbox(origin, otherCorner);
	}
	if (type == "sphere")
	{
		vec3 origin = jsonToVec3(j["origin"]);
		float radius = j["radius"];
		return new SphereHitbox(origin, radius);
	}

	return new Hitbox();
	//TODO: ANY OTHER TYPE...i wish c++ supported reflection
}