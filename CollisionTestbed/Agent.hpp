#include "Thing.hpp"

class Agent : public Thing
{
public:
	Agent(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));
	~Agent();

private:

};
