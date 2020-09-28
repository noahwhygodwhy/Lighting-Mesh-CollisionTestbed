#ifndef AGENT_H
#define AGENT_H
#include "Thing.hpp"
#include "Controller.hpp"

class Agent : public Thing
{
public:
	Agent(Model m, 
		Controller c,
		Hitbox h,
		vec3 cameraOffset = vec3(0, 0, 0),
		vec3 cameraVector = vec3(0, 0, 1),
		vec3 gunportOffset = vec3(0, 0, 0),
		vec3 gunportVector = vec3(0, 0, 1),
		vec3 position = vec3(0, 0, 0),
		vec3 velocity = vec3(0, 0, 0),
		vec3 orientation = vec3(0, 0, 0));
	Agent();
	~Agent();

	Controller getController();

private:
	Controller controller;
	vec3 cameraOffset;
	vec3 cameraVector;
	vec3 gunportOffset;
	vec3 gunportVector;

};
#endif