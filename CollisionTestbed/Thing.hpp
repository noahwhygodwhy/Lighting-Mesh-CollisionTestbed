#ifndef THING_H
#define THING_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Model.hpp"
#include "Hitbox.hpp"


using namespace std;
using namespace glm;



class IThing
{
public:
	virtual void tick(float deltaTime, GLFWwindow* window) = 0;
	virtual void draw(Shader shader) = 0;
};

//idk if this is needed, but i made it because i thought i might need it
enum class ThingType
{
	THING,
	AGENT,
	PLAYER,
	OBJECT,
	ENVIRONMENT,
	ERROR
};

/*struct positional
{
	mat4 transform;
	vec3 velocity;

	vec3 spinAxis;
	float spinRate;
	int weight = 1;//i'll have to calculate this later...idk how
};*/

class Thing : public IThing
{
	
public:
	Thing(Model m, vector<Hitbox*> preciseHitbox, vector<Hitbox*> generalHitbox, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0), ThingType = ThingType::THING);
	Thing();
	~Thing();



	void tick(float deltaTime, GLFWwindow* window);
	void draw(Shader shader);

	

	void impartForce(vec3 direction, float magnitude);
	void impartSpin(vec3 axis, float magnitude);
	void moveRelative(vec3 shift);
	void moveAbsolute(vec3 newPosition);
	void rotateRelative(vec3 axis, float degrees);
	void rotateAbsolute(vec3 axis, float degrees);
	void rotateSet(vec3 rotation);
	
	vec3 getUp();
	vec3 getForward();


	ThingType type;
	mat4 transform;
	vec3 velocity;
	vec3 spinAxis;
	float spinRate;
	int mass;//? idk how to calculate that but i'll figure it out.

	vector<Hitbox*> preciseHitbox;
	vector<Hitbox*> generalHitbox;
	vec3 maxs;
	vec3 mins;

	Model getModel();
private:
	Model model;
};
Thing* jsonToThing(string path);

#endif