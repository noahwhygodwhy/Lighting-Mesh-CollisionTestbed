#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Thing.hpp"
#include <GLFW/glfw3.h>

class Controller
{
public:
	Controller();
	~Controller();
	void giveThing(Thing* thing);
	void tick(float deltatime, GLFWwindow* window);
	Thing* thing;
private:
	
};

#endif