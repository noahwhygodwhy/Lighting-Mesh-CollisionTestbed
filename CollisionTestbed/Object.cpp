#include "Object.hpp"

Object::Object(Model m, Hitbox h, vec3 position, vec3 velocity, vec3 orientation) : Thing(m, h, position, velocity, orientation, ThingType::OBJECT)
{

}

Object::~Object()
{
}

