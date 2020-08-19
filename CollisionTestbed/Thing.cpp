#include "Thing.hpp"

Thing::Thing(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orentation = vec3(0, 0, 0))
{
	this->model = m;
	this->position = position;
	this->velocity = velocity;
	this->orientation = orientation;
}

Thing::~Thing()
{
}