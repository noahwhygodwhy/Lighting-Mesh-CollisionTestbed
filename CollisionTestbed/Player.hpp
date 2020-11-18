#ifndef PLAYER_H
#define PLAYER_H
#include "Agent.hpp"
#include "PlayerController.hpp"

class Player : public Agent
{
public:
	Player(Model m,
		PlayerController* c,
		Hitbox h,
		vec3 cameraOffset = vec3(0, 0, 0),
		vec3 cameraVector = vec3(0, 0, 1),
		vec3 gunportOffset = vec3(0, 0, 0),
		vec3 gunportVector = vec3(0, 0, 1),
		vec3 position = vec3(0, 0, 0),
		vec3 velocity = vec3(0, 0, 0),
		vec3 orientation = vec3(0, 0, 0),
		vec3 up = vec3(0, 0, 0),
		vec3 forward = vec3(0, 0, 0));
	Player();
	~Player();

	void tick(float deltaTime, GLFWwindow* window);
	PlayerController* getController();

private:
	vec3 cameraOffset;
	vec3 cameraVector;
	vec3 gunportOffset;
	vec3 gunportVector;

};
#endif