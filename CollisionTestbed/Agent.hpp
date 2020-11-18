#ifndef AGENT_H
#define AGENT_H
#include "Thing.hpp"
#include "Controller.hpp"

class Agent : public Thing
{
public:
	Agent(Model m, 
		Controller * c,
		Hitbox h,
		vec3 cameraOffset = vec3(0, 0, 0),
		vec3 cameraVector = vec3(0, 0, 1),
		vec3 gunportOffset = vec3(0, 0, 0),
		vec3 gunportVector = vec3(0, 0, 1),
		vec3 position = vec3(0, 0, 0),
		vec3 velocity = vec3(0, 0, 0),
		vec3 orientation = vec3(0, 0, 0),
		vec3 up = vec3(0, 0, 0),
		vec3 forward = vec3(0, 0, 0),
		ThingType thingtype = ThingType::AGENT);
	Agent();
	~Agent();

	void tick(float deltaTime, GLFWwindow* window);
	float getSpeed();
	Controller* getController();

private:
	Controller* controller;
	float speed;
	vec3 cameraOffset;
	vec3 cameraVector;
	vec3 gunportOffset;
	vec3 gunportVector;

};
#endif