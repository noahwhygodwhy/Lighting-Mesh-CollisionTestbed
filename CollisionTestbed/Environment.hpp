#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Object.hpp"
#include "Thing.hpp"

class Environment : public Thing
{
public:
	Environment(Model m, vector<Hitbox*> preciseHitbox, vector<Hitbox*> generalHitbox, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0), ThingType type = ThingType::ENVIRONMENT);
	~Environment();

private:

};
#endif