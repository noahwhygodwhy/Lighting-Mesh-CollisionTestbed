#include "Agent.hpp"
#include <string>

//Agent will eventually have a controller of sorts?
Agent::Agent(Model m,
	Controller c,
	Hitbox h,
	vec3 cameraOffset,
	vec3 cameraVector,
	vec3 gunportOffset,
	vec3 gunportVector,
	vec3 position,
	vec3 velocity,
	vec3 orientation)
	:Thing(m, h, position, velocity, orientation, ThingType::AGENT)
{ 
	this->cameraOffset = cameraOffset;
	this->cameraVector = cameraVector;
	this->gunportOffset = gunportOffset;
	this->gunportVector = gunportVector;
	this->controller = c;
	this->controller.giveThing(this);
}

Agent::Agent():Thing()
{
	this->cameraOffset = vec3(0);
	this->cameraVector = vec3(0);
	this->gunportOffset = vec3(0);
	this->gunportVector = vec3(0);
}

void Agent::tick(float deltaTime)
{
	this->controller.tick(deltaTime);
}

Agent::~Agent()
{
}

/*Controller Agent::getController()
{
	return this->controller;
}*/