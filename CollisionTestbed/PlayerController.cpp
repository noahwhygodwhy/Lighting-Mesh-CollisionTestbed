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
	double xpos;
	double ypos;

	glfwGetCursorPos(window, &xpos, &ypos);

	xpos = xpos / 5000;
	ypos = ypos / 5000;
	this->thing->transform = glm::rotate(this->thing->transform, (float)(this->lastX - xpos), vec3(0, 1, 0));

	lastX = xpos;
	lastY = ypos;

	vec2 direction = vec2(glfwGetKey(window, GLFW_KEY_D)- glfwGetKey(window, GLFW_KEY_A), glfwGetKey(window, GLFW_KEY_W) - glfwGetKey(window, GLFW_KEY_S));
	
	//printf("forward, %f, %f, %f\n", this->thing->getForward().x, this->thing->getForward().y, this->thing->getForward().z);
	vec2 newDirection = vec3(0.0f);
	if (direction.x != 0 or direction.y !=0)
	{
		direction = glm::normalize(direction);
		vec2 trueForward = vec2(0, 1);
		vec2 thingsFoward = normalize(vec2(this->thing->getForward().x, this->thing->getForward().z));
		vec2 quoteoriginquote = vec2(0, 0);

		vec2 norm1 = glm::normalize(trueForward - quoteoriginquote);
		vec2 norm2 = glm::normalize(thingsFoward - quoteoriginquote);
		float theDot = glm::dot(norm1, norm2);
		float angleRads = glm::acos(theDot);

		newDirection = glm::rotate(direction, angleRads);
	}

	this->thing->transform = glm::translate(this->thing->transform, vec3(newDirection.y,0, newDirection.x));
}