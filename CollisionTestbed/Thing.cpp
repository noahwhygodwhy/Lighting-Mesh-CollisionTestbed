#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Thing.hpp"
#include "Model.hpp"

#define GLM_ENABLE_EXPERIMENTAL

using namespace std;
using namespace nlohmann;

Thing::Thing(Model m, vec3 position, vec3 velocity, vec3 orientation, ThingType type)
{
	this->model = m;
	this->transform = mat4(1.0f);
	this->transform = glm::translate(this->transform, position);
	this->transform = glm::rotate(this->transform, radians(orientation.x), vec3(1, 0, 0));
	this->transform = ::rotate(this->transform, radians(orientation.y), vec3(0, 1, 0));
	this->transform = glm::rotate(this->transform, radians(orientation.z), vec3(1, 0, 1));
	this->velocity = velocity;
	this->type = type;
}


Thing::Thing()
{	
	this->type = ThingType::ERROR;
	this->model = Model();
	this->transform = mat4(1.0f);
	this->velocity = vec3(0, 0, 0);
}

Thing::~Thing()
{

}

Thing Thing::fromJson(string path)
{
	ifstream theFile;
	theFile.open(path);
	if (!theFile.good())
	{
		printf("error loading model from json:\n%s\n", path);
		return Thing(); //default things have a type of ERROR, so this indicates it's wrong
	}

	json j;
	theFile >> j;
}

void Thing::tick(float deltaTime)
{
	//move the object according to time
}

void Thing::draw(Shader shader)
{
	model.draw(shader, transform);
}




//TODO: BEGIN
void Thing::impartForce(vec3 direction, float magnitude)
{

}
void Thing::impartSpin(vec3 axis, float magnitude)
{

}
void Thing::moveRelative(vec3 shift)
{

}
void Thing::moveAbsolute(vec3 newPosition)
{

}
void Thing::rotateRelative(vec3 axis, float degrees)
{

}
void Thing::rotateAbsolute(vec3 axis, float degrees)
{

}
void Thing::rotateSet(vec3 rotation)
{

}
//TODO: END