#include "Agent.hpp"


//Agent will eventually have a controller of sorts?
Agent::Agent(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0)) : Thing(m, position, velocity, orientation)
{
}

Agent::~Agent()
{
}