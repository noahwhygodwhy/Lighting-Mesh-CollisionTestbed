#include "Player.hpp"
#include "glm/glm.hpp"
#include <glm/gtx/vector_angle.hpp>
#include "glm/gtx/rotate_vector.hpp"
Player::Player():Agent()
{

}

Player::Player(Model m,
	PlayerController* c,
	vector<Hitbox*> preciseHitbox,
	vector<Hitbox*> generalHitbox,
	Camera camera,
	vec3 cameraOffset,
	vec3 cameraVector,
	vec3 gunportOffset,
	vec3 gunportVector,
	vec3 position,
	vec3 velocity,
	vec3 orientation) : Agent(m, c, preciseHitbox, generalHitbox, cameraOffset, cameraVector, gunportOffset, gunportVector, position, velocity, orientation, ThingType::PLAYER)
{
	this->camera = camera;
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
	return this->camera.getView(this->transform);
	/*
	vec3 up = vec3(0, 1, 0);
	vec3 forward = vec3(0, 0, 1);

	vec3 thingsUp = this->getUp();
	vec3 thingsForward = this->getForward();

	qua r1 = glm::rotation(up, thingsUp);
	qua r2 = glm::rotation(forward, thingsForward);

	vec3 trueCameraOffset = glm::rotate(r1, this->cameraOffset);
	trueCameraOffset = glm::rotate(r2, trueCameraOffset);

	mat4 cameraTransform = glm::translate(transform, trueCameraOffset);
	
	//TODO: Adjust for camera offset
	//return lookAt(position, position + front, up);


	return glm::lookAt(vec3(cameraTransform[3]), vec3(cameraTransform[3] - cameraTransform[2]), vec3(cameraTransform[1]));
	*/
}