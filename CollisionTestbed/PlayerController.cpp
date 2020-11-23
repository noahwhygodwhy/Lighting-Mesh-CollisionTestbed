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
	//mat4 t = this->thing->transform;
	//thank you steven m lavalle from cambridge
	//float yaw = atan2(t[1][0], t[0][0]);
	//float pitch = atan2(-t[2][0], sqrt((t[2][1] * t[2][1]) + (t[2][2]) * t[2][2]));


	/*
	printf("current yaw: %f, current pitch: %f\n", yaw, pitch);
	xpos = xpos;
	ypos = ypos;

	if (!(lastX == 69.696969 && lastY == 69.696969))
	{
		float changeX = this->lastX - xpos;
		float changeY = this->lastY - ypos;
		printf("changex: %f\n", changeX);
		yaw += changeX * this->mouseSensitivity;
		pitch += changeY * this->mouseSensitivity;
		//printf("changex, %f\n", changeX);
	}
	else
	{
		//printf("first instance\n");
	}
	
	printf("calculated yaw: %f, calculated pitch: %f\n", yaw, pitch);
	*/


	//((Player*)this->thing)->camera.mouseInput(xpos, ypos, true);

	/*vec3 f;
	f.x = cos(radians(yaw)) * cos(radians(pitch));
	f.y = sin(radians(pitch));
	f.z = sin(radians(yaw)) * cos(radians(pitch));

	vec3 front = normalize(f);
	vec3 right = normalize(cross(front, vec3(0, 1, 0)));
	vec3 up = normalize(cross(right, front));

	this->thing->transform[0] = vec4(right, 0);
	this->thing->transform[1] = vec4(up, 0);
	this->thing->transform[2] = vec4(-front, 0);
	//printf("current position is %f, %f, %f\n", t[3][0], t[3][1], t[3][2]);*/

	//t = lookAt(vec3(t[3]), vec3(t[3]) + front, up);
	//t[3] = this->thing->transform[3];
	//this->thing->transform = t;

	/*vec3 flatFront = normalize(-vec3(this->thing->transform[2][0], 0, this->thing->transform[2][2]));
	vec3 right = normalize(cross(flatFront, vec3(0,1,0)));
	vec3 up = normalize(cross(vec3(this->thing->transform[0]), flatFront));

	this->thing->transform[0] = vec4(right, 0);
	this->thing->transform[1] = vec4(up, 0);
	this->thing->transform[2] = vec4(flatFront, 0);*/

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