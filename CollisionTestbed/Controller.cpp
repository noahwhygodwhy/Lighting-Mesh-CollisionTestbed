#include "Controller.hpp"

Controller::Controller()
{
	this->thing = (Thing*)0;
	this->id = num++;
	printf("creating controller %i\n", this->id);
}
void Controller::giveThing(Thing* thing)
{
	printf("controller id is %i\n", this->id);
	printf("being given thing\n");
	printf("%p\n", thing);
	this->thing = thing;
	printf("my thing is now:\n");
	printf("%p\n", this->thing);

}
void Controller::tick(float delta, GLFWwindow* window)
{
	this->thing->rotateRelative(vec3(0, 1, 0), 1);// 0.36f * delta);
}
Controller::~Controller()
{

}