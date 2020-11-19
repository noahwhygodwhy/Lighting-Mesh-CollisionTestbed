#include "PlayerController.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include <glm/gtx/string_cast.hpp>

PlayerController::PlayerController() : Controller()
{
	printf("player controller constructor\n");
}

PlayerController::~PlayerController()
{

}
void PlayerController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods, float speed)
{
	/*if (key == GLFW_KEY_W)
	{
		printf("W");
	}
	if (key == GLFW_KEY_S)
	{
		printf("S");
	}
	if (key == GLFW_KEY_A)
	{
		printf("A");
	}
	if (key == GLFW_KEY_D)
	{
		printf("D");
	}*/
}
void PlayerController::mouseButtCallback(GLFWwindow* window, int button, int action, int mods)
{

}
void PlayerController::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{

}
void PlayerController::tick(float deltaTime, GLFWwindow* window)
{
	vec2 direction = vec2(glfwGetKey(window, GLFW_KEY_W)- glfwGetKey(window, GLFW_KEY_S), glfwGetKey(window, GLFW_KEY_A)- glfwGetKey(window, GLFW_KEY_D));
	
	vec2 newDirection = direction;
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
	else
	{
		newDirection = vec2(0.0f);
	}
	this->thing->transform = glm::translate(this->thing->transform, vec3(newDirection.y,0, newDirection.x));
	
}