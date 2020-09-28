#include "Environment.hpp"

Environment::Environment(Model m, Hitbox h, vec3 position, vec3 velocity, vec3 orientation) : Thing(m, h, position, velocity, orientation, ThingType::ENVIRONMENT)
{

}

Environment::~Environment()
{
}