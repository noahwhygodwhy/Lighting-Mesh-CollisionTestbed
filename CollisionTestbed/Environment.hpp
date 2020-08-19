#include "Thing.hpp"

class Environment : public Thing
{
public:
	Environment(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));
	~Environment();

private:

};

Environment::Environment(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0)) : Thing(m, position, velocity, orientation)
{

}

Environment::~Environment()
{
}