
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.hpp"


using namespace std;
using namespace glm;

class Thing
{
public:
	Thing(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0));
	~Thing();
	void tick(float deltaTime);
	//void impart force(..?);
private:
	vec3 position;
	vec3 orientation; //TODO: maybe figure out quaternions...
	vec3 velocity;
	int weight;//? idk how to calculate that but i'll figure it out.
	Model model;
};
