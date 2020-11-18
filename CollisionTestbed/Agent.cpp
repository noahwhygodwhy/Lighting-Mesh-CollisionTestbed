#include "Agent.hpp"
#include <string>

//Agent will eventually have a controller of sorts?
Agent::Agent(Model m,
	Controller * c,
	Hitbox h,
	vec3 cameraOffset,
	vec3 cameraVector,
	vec3 gunportOffset,
	vec3 gunportVector,
	vec3 position,
	vec3 velocity,
	vec3 orientation,
	vec3 up,
	vec3 forward,
	ThingType thingtype)
	:Thing(m, h, position, velocity, orientation, up, forward, thingtype)
{ 
	this->cameraOffset = cameraOffset;
	this->cameraVector = cameraVector;
	this->gunportOffset = gunportOffset;
	this->gunportVector = gunportVector;
	this->controller = c;
	printf("id of controller for agent construtor: %i\n", this->controller->id);
	this->controller->giveThing(this);
	printf("id of controller for agent construtor2: %i\n", this->controller->id);
	this->speed = 1.0;
}

Controller* Agent::getController()
{
	return this->controller;
}

Agent::Agent():Thing()
{
	this->cameraOffset = vec3(0);
	this->cameraVector = vec3(0);
	this->gunportOffset = vec3(0);
	this->gunportVector = vec3(0);
	this->speed = 1.0;
}

void Agent::tick(float deltaTime, GLFWwindow* window)
{
	this->controller->tick(deltaTime, window);
}

Agent::~Agent()
{
}
float Agent::getSpeed()
{
	return this->speed;
}
