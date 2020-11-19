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
	//Player* p = dynamic_cast<Player*>(jsonToThing("player1"));
	Player* p = (Player*) jsonToThing("player2");
	Agent* a = (Agent*)jsonToThing("agent1");
	
	r.addThing(a);
	r.setPlayer(p);
	printf("###running\n");
	r.run();
	printf("###ending\n");
}