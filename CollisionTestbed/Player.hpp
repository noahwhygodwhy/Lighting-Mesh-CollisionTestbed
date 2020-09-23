#include "Agent.hpp"
#include <string>
class Player : public Agent
{
public:
	Player(Model m, Controller c, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));
	Player(string path, Controller c, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));//TODO:
	~Player();

private:

};
