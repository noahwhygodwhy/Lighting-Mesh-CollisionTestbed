#include "Controller.hpp"

Controller::Controller()
{
	this->thing = (Thing*)0;
}
void Controller::giveThing(Thing* thing)
{
	this->thing = thing;
}
void Controller::tick(float delta, GLFWwindow* window)
{
	this->thing->rotateRelative(vec3(0, 1, 0), 1);// 0.36f * delta);
}
Controller::~Controller()
{

}