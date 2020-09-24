#include "Player.hpp"

Player::Player(Model m, Controller c, vec3 position, vec3 velocity, vec3 orientation) : Agent(m, c, position, velocity, orientation)
{

}
Player::Player(string path, Controller c, vec3 position, vec3 velocity, vec3 orientation) : Agent(path, c, position, velocity, orientation)
{

}

Player::Player() : Agent((string) "", Controller(), vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)) //This is probably superbad, but idk how else to handle it
{
	printf("ERROR, THIS SHOULD NEVER BE CALLED\n");
	exit(0);
}

Player::~Player()
{
}

