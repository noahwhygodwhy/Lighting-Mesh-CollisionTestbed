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
	((Player*)this->thing)->camera.mouseInput(xpos, ypos, true);
	this->thing->transform[0];

	vec3 flatFront = -vec3(this->thing->transform[2][0], 0, this->thing->transform[2][2]);

	vec3 right = normalize(cross(flatFront, vec3(0,1,0)));
	vec3 up = normalize(cross(vec3(this->thing->transform[0]), flatFront));

	this->thing->transform[0] = vec4(right, 0);
	this->thing->transform[1] = vec4(up, 0);
	this->thing->transform[2] = vec4(flatFront, 0);

	//this->thing->transform = glm::rotate(this->thing->transform, (float) glm::radians(xpos/10000), glm::vec3(0.0f, 1.0f, 0.0f));
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
	((Player*)this->thing)->camera.move(vec3(newDirection.y, 0, newDirection.x));
	
}