#include "Player.hpp"

Player::Player():Agent()
{

}

Player::Player(Model m,
	Controller c,
	Hitbox h,
	vec3 cameraOffset,
	vec3 cameraVector,
	vec3 gunportOffset,
	vec3 gunportVector,
	vec3 position,
	vec3 velocity,
	vec3 orientation,
	vec3 up,
	vec3 forward) : Agent(m, c, h, cameraOffset, cameraVector, gunportOffset, gunportVector, position, velocity, orientation, up, forward, ThingType::PLAYER)
{

}