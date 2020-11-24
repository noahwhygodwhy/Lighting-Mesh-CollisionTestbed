#include "Agent.hpp"
#include <string>
#include <glm/gtx/vector_angle.hpp>
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/string_cast.hpp"
//Agent will eventually have a controller of sorts?
Agent::Agent(Model m,
	Controller * c,
	vector<Hitbox*> preciseHitbox,
	vector<Hitbox*> generalHitbox,
	vec3 cameraOffset,
	vec3 cameraVector,
	vec3 gunportOffset,
	vec3 gunportVector,
	vec3 position,
	vec3 velocity,
	vec3 orientation,
	ThingType thingtype)
	:Thing(m, preciseHitbox, generalHitbox, position, velocity, orientation, thingtype)
{ 
	this->cameraOffset = cameraOffset;
	this->cameraVector = cameraVector;
	this->gunportOffset = gunportOffset;
	this->gunportVector = gunportVector;
	this->controller = c;
	this->controller->giveThing(this);
	this->speed = 1.0;
}

Controller* Agent::getController()
{
	return this->controller;
}


Agent::Agent():Thing()
{
	this->controller = new Controller();
	this->controller->giveThing(this);
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
