#include "Object.hpp"

Object::Object(Model m, Hitbox h, vec3 position, vec3 velocity, vec3 orientation, vec3 up, vec3 forward) : Thing(m, h, position, velocity, orientation, up, forward, ThingType::OBJECT)
{

}

Object::~Object()
{
}

