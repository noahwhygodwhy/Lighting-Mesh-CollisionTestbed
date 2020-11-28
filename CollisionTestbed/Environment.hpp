#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Thing.hpp"

class Environment : public Thing
{
public:
	Environment(Model m, vector<Hitbox*> preciseHitbox, vector<Hitbox*> generalHitbox, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0), ThingType type = ThingType::ENVIRONMENT);
	~Environment();
	virtual void tick(float deltaTime, GLFWwindow* window);
	void gravityTick(float deltaTime, GLFWwindow* window);
private:

};
#endif