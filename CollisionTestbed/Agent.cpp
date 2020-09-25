#include "Agent.hpp"
#include <string>

//Agent will eventually have a controller of sorts?
Agent::Agent(Model m, Controller c, vec3 position, vec3 velocity, vec3 orientation) : Thing(m, position, velocity, orientation)
{
	this->controller = c;
}
Agent::Agent(string path, Controller c, vec3 position, vec3 velocity, vec3 orientation) : Thing(path, position, velocity, orientation)
{
	this->controller = c;
}

Agent::Agent():Thing()
{

}

Agent::~Agent()
{
}

Controller Agent::getController()
{
	return this->controller;
}