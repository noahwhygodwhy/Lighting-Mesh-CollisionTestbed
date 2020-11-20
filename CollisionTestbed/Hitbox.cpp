#include "Hitbox.hpp"
#include "CylinderHitbox.hpp"
Hitbox::Hitbox(vec3 origin)
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
		return CylinderHitbox(vec3(0), radius, height);
	}
	if (type == "objFile")
	{
		string filename = j["filename"];
		return objHitbox(filename);
	}

	return Hitbox();
	//TODO: ANY OTHER TYPE...i wish c++ supported reflection
}