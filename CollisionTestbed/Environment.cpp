#include "Environment.hpp"

Environment::Environment(Model m, vector<Hitbox*> preciseHitbox, vector<Hitbox*> generalHitbox, vec3 position, vec3 velocity, vec3 orientation) : Thing(m, preciseHitbox, generalHitbox, position, velocity, orientation, ThingType::ENVIRONMENT)
{

}

Environment::~Environment()
{
}