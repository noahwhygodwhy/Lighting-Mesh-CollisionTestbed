#include <stdio.h>
#include "Renderer.hpp"
#include "Agent.hpp"
#include "Thing.hpp"
#include "Player.hpp"
#include "Controller.hpp"
#include "PlayerController.hpp"

#include <iostream>
#include <fstream>


using namespace std;

int main(void)
{

	printf("###starting\n");
	Renderer r = Renderer(1920, 1080);
	printf("###initializing\n");
	r.initialize();
	printf("###adding model\n");
	//r.addModel("C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/brickCube/brickCube.obj");

	//string Agent1Path = "C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/survival backpack/backpack.obj";
	//string Agent2Path = "C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/Agent1/agent1.obj";

	ofstream myFile("theweirdfilenameIcameupwith");
	myFile << "THE FILE CONTESNTS";
	myFile.close();

	Thing* a = jsonToThing("agent1");
	Agent* b = dynamic_cast<Agent*>(jsonToThing("agent1"));
	Agent* c = static_cast<Agent*>(jsonToThing("agent1"));
	Agent* p = static_cast<Agent*>(jsonToThing("agent1"));
	b->moveRelative(vec3(5, 0, 0));
	c->moveRelative(vec3(10, 0, 0));
	//Agent b = js("agent1");
	
	//Thing a = jsonToThing("C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/agent1/agent1.json");

	//Model playerModel = Model(Agent2Path.c_str());
	//Model otherModel = Model(Agent2Path.c_str());
	//Agent p1 = Agent(playerModel, Controller(), vec3(0, 0, 0));
	//Player p1 = Player("C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/Agent1", PlayerController(), vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0));
	//Agent p2 = Agent(otherModel, Controller(), vec3(5, 0, 0));


	//r.addPlayer(p1);
	//r.addThing(p1);
	//r.addThing(p2);
	//r.addThing(a);
	//r.addThing(b);
	//r.addThing(c);
	r.setPlayer(p);
	//r.addPlayer(b);
	printf("###running\n");
	r.run();
	printf("###ending\n");
}