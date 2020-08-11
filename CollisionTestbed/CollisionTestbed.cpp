#include <stdio.h>
#include "Renderer.hpp"

using namespace std;

int main(void)
{
	printf("###starting\n");
	Renderer r = Renderer(1960, 1080);
	printf("###initializing\n");
	r.initialize();
	printf("###ending\n");
}