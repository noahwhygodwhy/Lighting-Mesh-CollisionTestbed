#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Thing.hpp"

class Controller
{
public:
	Controller();
	~Controller();
	void giveThing(Thing* thing);
	void tick(float deltatime);
private:
	Thing* thing;
};

#endif