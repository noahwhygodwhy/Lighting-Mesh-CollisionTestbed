#include "Thing.hpp"

Thing::Thing(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0))
{
	this->model = m;
	this->position = position;
	this->velocity = velocity;
	this->orientation = orientation;
}

Thing::~Thing()
{
}


void tick(float deltaTime)
{

}





//TODO: BEGIN
void Thing::tick(float deltaTime)
{

}
void Thing::impartForce(vec3 direction, float magnitude)
{

}
void Thing::impartSpin(vec3 axis, float magnitude)
{

}
void Thing::moveRelative(vec3 shift)
{

}
void Thing::moveAbsolute(vec3 newPosition)
{

}
void Thing::rotateRelative(vec3 axis, float degrees)
{

}
void Thing::rotateAbsolute(vec3 axis, float degrees)
{

}
void Thing::rotateSet(vec3 rotation)
{

}
//TODO: END