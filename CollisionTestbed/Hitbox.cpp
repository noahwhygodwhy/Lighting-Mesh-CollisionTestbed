#include "Hitbox.hpp"
#include "CylinderHitbox.hpp"
#include "CuboidHitbox.hpp"
Hitbox::Hitbox(vec3 origin, HitboxType type)
{
	this->origin = origin;
}

Hitbox::Hitbox()
{
	this->origin = vec3(0);
}

Hitbox::~Hitbox()
{
}

vec3 jsonToVec3(json j)
{
	return vec3(j["x"], j["y"], j["z"]);
}
Hitbox jsonToHitbox(json j)
{
	string type = j["type"];
	if (type == "cylinder")
	{
		float radius = j["radius"];
		float height = j["height"];
		vec3 origin = jsonToVec3(j["origin"]);
		return CylinderHitbox(origin, radius, height);
	}
	if (type == "cuboid")
	{
		vec3 origin = jsonToVec3(j["origin"]);
		vec3 dims = jsonToVec3(j["dims"]);
		vec3 otherCorner = origin + dims;
		return CuboidHitbox(origin, otherCorner);
	}

	return Hitbox();
	//TODO: ANY OTHER TYPE...i wish c++ supported reflection
}