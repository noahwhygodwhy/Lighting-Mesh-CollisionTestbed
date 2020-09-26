#include "Object.hpp"

Object::Object(Model m, vec3 position, vec3 velocity, vec3 orientation) : Thing(m, position, velocity, orientation, ThingType::OBJECT)
{

}

Object::~Object()
{
}

