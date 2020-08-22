#include "Object.hpp"

Object::Object(Model m, vec3 position = vec3(0, 0, 0), vec3 velocity = vec3(0, 0, 0), vec3 orientation = vec3(0, 0, 0)) : Thing(m, position, velocity, orientation)
{

}

Object::~Object()
{
}

