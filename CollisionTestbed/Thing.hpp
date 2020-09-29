#ifndef THING_H
#define THING_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.hpp"
#include <string>
#include "Hitbox.hpp"


using namespace std;
using namespace glm;

enum class ThingType
{

	THING,
	AGENT,
	OBJECT,
	ENVIRONMENT,
	ERROR

};

class Thing
{
	
public:
	Thing(Model m, Hitbox h, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0), ThingType = ThingType::THING);
	Thing();
	~Thing();



	void tick(float deltaTime);
	void draw(Shader shader);

	

	void impartForce(vec3 direction, float magnitude);
	void impartSpin(vec3 axis, float magnitude);
	void moveRelative(vec3 shift);
	void moveAbsolute(vec3 newPosition);
	void rotateRelative(vec3 axis, float degrees);
	void rotateAbsolute(vec3 axis, float degrees);
	void rotateSet(vec3 rotation);

	//void impart force(..?);
private:
	ThingType type;
	mat4 transform;
	//vec3 position;
	//vec3 orientation; //TODO: maybe figure out quaternions...
	vec3 velocity;
	vec3 spinAxis;
	float spinRate;
	int weight;//? idk how to calculate that but i'll figure it out.
	Model model;
};

#endif