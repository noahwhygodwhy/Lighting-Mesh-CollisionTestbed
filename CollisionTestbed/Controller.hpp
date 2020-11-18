#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Thing.hpp"

static int num = 0;
class Controller
{
public:
	Controller();
	~Controller();
	void giveThing(Thing* thing);
	void tick(float deltatime, GLFWwindow* window);
	Thing* thing;
	int id;
private:
	
};

#endif