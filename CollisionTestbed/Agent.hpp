#ifndef AGENT_H
#define AGENT_H
#include "Thing.hpp"
#include "Controller.hpp"

class Agent : public Thing
{
public:
	Agent(Model m, Controller c, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));
	Agent(string path, Controller c, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));
	~Agent();

	Controller getController();

private:
	Controller controller;

};
#endif