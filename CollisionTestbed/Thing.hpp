
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.hpp"


using namespace std;
using namespace glm;

class Thing
{
public:
	Thing(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orentation = vec3(0, 0, 0));
	~Thing();

private:
	vec3 position;
	vec3 orientation; //TODO: maybe figure out quaternions...
	vec3 velocity;
	Model model;
};

Thing::Thing(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orentation = vec3(0, 0, 0))
{//WHYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
	this->model = m;
	this->position = position;
	this->velocity = velocity;
	this->orientation = orientation;
}

Thing::~Thing()
{
}