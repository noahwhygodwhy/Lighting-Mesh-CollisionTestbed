#include <stdio.h>
#include "Renderer.hpp"
#include "Agent.hpp"
#include "Thing.hpp"
#include "Player.hpp"
#include "Controller.hpp"
#include "PlayerController.hpp"

using namespace std;

int main(void)
{
	printf("###starting\n");
	Renderer r = Renderer(1920, 1080);
	printf("###initializing\n");
	r.initialize();
	printf("###adding model\n");
	//r.addModel("C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/brickCube/brickCube.obj");

	Model playerModel = Model("C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/survival backpack/backpack.obj");
	Player p1 = Player(playerModel, PlayerController(), vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0));
	Agent p2 = Agent(playerModel, Controller());// , vec3(0, 0, 0));


	r.addPlayer(p1);

	r.addThing(p2);
	
	printf("###running\n");
	r.run();
	printf("###ending\n");
}