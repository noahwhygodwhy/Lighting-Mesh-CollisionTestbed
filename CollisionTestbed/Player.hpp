#ifndef PLAYER_H
#define PLAYER_H
#include "Agent.hpp"
#include "PlayerController.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Player : public Agent
{
public:
	Player(Model m,
		PlayerController* c,
		vector<Hitbox> preciseHitbox,
		Hitbox generalHitbox,
		vec3 cameraOffset = vec3(0, 0, 0),
		vec3 cameraVector = vec3(0, 0, 1),
		vec3 gunportOffset = vec3(0, 0, 0),
		vec3 gunportVector = vec3(0, 0, 1),
		vec3 position = vec3(0, 0, 0),
		vec3 velocity = vec3(0, 0, 0),
		vec3 orientation = vec3(0, 0, 0));
	Player();
	~Player();
	mat4 getView();
	void tick(float deltaTime, GLFWwindow* window);
	PlayerController* getController();

private:

};
#endif