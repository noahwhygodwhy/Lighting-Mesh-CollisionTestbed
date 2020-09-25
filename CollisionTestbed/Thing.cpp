#include "Thing.hpp"
#include "Model.hpp"
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#define GLM_ENABLE_EXPERIMENTAL

Thing::Thing(Model m, vec3 position, vec3 velocity, vec3 orientation)
{
	this->model = m;
	this->transform = mat4(1.0f);
	this->transform = glm::translate(this->transform, position);
	this->transform = glm::rotate(this->transform, radians(orientation.x), vec3(1, 0, 0));
	this->transform = ::rotate(this->transform, radians(orientation.y), vec3(0, 1, 0));
	this->transform = glm::rotate(this->transform, radians(orientation.z), vec3(1, 0, 1));
	this->velocity = velocity;
}

Thing::Thing(string path, vec3 position, vec3 velocity, vec3 orientation)
{
	this->model = Model(path.c_str());
	this->transform = mat4(1.0f);
	this->transform = glm::translate(this->transform, position);
	this->transform = glm::rotate(this->transform, radians(orientation.x), vec3(1, 0, 0));
	this->transform = glm::rotate(this->transform, radians(orientation.y), vec3(0, 1, 0));
	this->transform = glm::rotate(this->transform, radians(orientation.z), vec3(1, 0, 1));
	this->velocity = velocity;
}

Thing::Thing()
{
	this->model = Model();
	this->transform = mat4(1.0f);
	this->velocity = vec3(0, 0, 0);
}

Thing::~Thing()
{

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