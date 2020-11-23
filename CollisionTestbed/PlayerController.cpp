#include "PlayerController.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Player.hpp"

PlayerController::PlayerController() : Controller()
{

}

PlayerController::~PlayerController()
{

}
void PlayerController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods, float speed)
{
}
void PlayerController::mouseButtCallback(GLFWwindow* window, int button, int action, int mods)
{
}
void PlayerController::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
}






void PlayerController::tick(float deltaTime, GLFWwindow* window)
{
	//printf("player controller tick\n");
	double xpos;
	double ypos;

	glfwGetCursorPos(window, &xpos, &ypos);

	xpos = xpos / 2000;
	ypos = ypos / 2000;
	this->thing->transform = glm::rotate(this->thing->transform, (float)(this->lastX - xpos), vec3(0, 1, 0));
	((Player*)this->thing)->camera.transform = glm::rotate(((Player*)this->thing)->camera.transform, (float)(this->lastY - ypos), vec3(1, 0, 0));
	lastX = xpos;
	lastY = ypos;


	vec2 direction = vec2(glfwGetKey(window, GLFW_KEY_D)- glfwGetKey(window, GLFW_KEY_A), glfwGetKey(window, GLFW_KEY_W) - glfwGetKey(window, GLFW_KEY_S));
	this->thing->transform = glm::translate(this->thing->transform, vec3(direction.x, 0, -direction.y));
	//printf("%s\n", glm::to_string(this->thing->transform).c_str());
}