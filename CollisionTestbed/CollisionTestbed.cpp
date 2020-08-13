#include <stdio.h>
#include "Renderer.hpp"

using namespace std;

int main(void)
{
	printf("###starting\n");
	Renderer r = Renderer(1960, 1080);
	printf("###initializing\n");
	r.initialize();
	printf("###adding model\n");
	r.addModel("C:\\Users\\noahm\\source\\repos\\CollisionTestbed\\CollisionTestbed\\survival backpack\\Survival_BackPack_2.fbx");
	printf("###running\n");
	r.run();
	printf("###ending\n");
}