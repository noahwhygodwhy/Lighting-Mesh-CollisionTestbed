#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <GLFW/glfw3.h>
#include "Controller.hpp"
//#include "Camera.hpp"

class PlayerController : public Controller
{
public:
	PlayerController();
	~PlayerController();
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods, float speed);
	void mouseButtCallback(GLFWwindow* window, int button, int action, int mods);
	void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

private:

};


#endif