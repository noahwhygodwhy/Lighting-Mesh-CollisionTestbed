#include "Object.hpp"

Object::Object(Model m, vector<Hitbox*> preciseHitbox, vector<Hitbox*> generalHitbox, vec3 position, vec3 velocity, vec3 orientation) : Thing(m, preciseHitbox, generalHitbox, position, velocity, orientation, ThingType::OBJECT)
{

}

Object::~Object()
{
}

