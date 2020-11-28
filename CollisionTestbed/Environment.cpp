#include "Environment.hpp"

Environment::Environment(Model m, vector<Hitbox*> preciseHitbox, vector<Hitbox*> generalHitbox, vec3 position, vec3 velocity, vec3 orientation, ThingType type) : Thing(m, preciseHitbox, generalHitbox, position, velocity, orientation, type)
{

}

Environment::~Environment()
{
}

void Environment::tick(float deltaTime, GLFWwindow* window)
{
}
void Environment::gravityTick(float deltaTime, GLFWwindow* window)
{
}