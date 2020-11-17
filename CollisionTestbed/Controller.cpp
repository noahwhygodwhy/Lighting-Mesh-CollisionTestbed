#include "Controller.hpp"

Controller::Controller()
{

}
void Controller::giveThing(Thing* thing)
{
	this->thing = thing;
}
void Controller::tick(float delta)
{
	this->thing->rotateRelative(vec3(0, 1, 0), 1);// 0.36f * delta);
}
Controller::~Controller()
{

}