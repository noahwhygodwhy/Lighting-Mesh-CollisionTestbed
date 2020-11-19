#include "Player.hpp"

Player::Player():Agent()
{

}

Player::Player(Model m,
	PlayerController* c,
	Hitbox h,
	vec3 cameraOffset,
	vec3 cameraVector,
	vec3 gunportOffset,
	vec3 gunportVector,
	vec3 position,
	vec3 velocity,
	vec3 orientation) : Agent(m, c, h, cameraOffset, cameraVector, gunportOffset, gunportVector, position, velocity, orientation, ThingType::PLAYER)
{
}
void Player::tick(float deltaTime, GLFWwindow* window)
{
	this->getController()->tick(deltaTime, window);
}


PlayerController* Player::getController()
{
	return (PlayerController*)this->Agent::getController();
}


mat4 Player::getView()
{
	//TODO:
	// make a new transform
	// adjust that transform per the camera offset/camera vector
	// return a lookat using that transform
	//

	//TODO: Adjust for camera offset
	return lookAt(position, position + front, up);


	return glm::lookAt(vec3(this->transform[3]), vec3(this->transform[3] - this->transform[2]), vec3(this->transform[1])+this->cameraOffset);
}