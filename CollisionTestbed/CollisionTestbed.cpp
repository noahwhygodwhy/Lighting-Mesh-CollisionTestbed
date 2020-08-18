#include <stdio.h>
#include "Renderer.hpp"

using namespace std;

int main(void)
{
	printf("###starting\n");
	Renderer r = Renderer(1920, 1080);
	printf("###initializing\n");
	r.initialize();
	printf("###adding model\n");
	//r.addModel("C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/brickCube/brickCube.obj");
	r.addModel("C:/Users/noahm/source/repos/CollisionTestbed/CollisionTestbed/survival backpack/backpack.obj");
	printf("###running\n");
	r.run();
	printf("###ending\n");
}