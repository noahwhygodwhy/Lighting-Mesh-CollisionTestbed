#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Model.hpp"

#include "Thing.hpp"
#include "Agent.hpp"
#include "Environment.hpp"
#include "Object.hpp"
#


#define GLM_ENABLE_EXPERIMENTAL

using namespace std;
using namespace nlohmann;
Thing::Thing(Model m, Hitbox h, vec3 position, vec3 velocity, vec3 orientation, ThingType type)
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
	this->transform = glm::translate(this->transform, shift);
}
void Thing::moveAbsolute(vec3 newPosition)
{

}
void Thing::rotateRelative(vec3 axis, float degrees)
{
	this->transform = glm::rotate(this->transform, glm::radians(degrees), axis);
}
void Thing::rotateAbsolute(vec3 axis, float degrees)
{

}
void Thing::rotateSet(vec3 rotation)
{

}
//TODO: END

static unordered_map<std::string, Model> loadedModels; //TODO: might need to be a model pointer, not a model
Thing* jsonToThing(string thingTitle)
{

	string path = thingTitle + "/" + thingTitle + ".json";
	ifstream theFile;
	theFile.open(path);
	if (!theFile.good())
	{
		printf("error loading model from json:\n%s\n", path.c_str());
		return new Thing(); //default things have a type of ERROR, so this indicates it's wrong
	}
	printf("file is good: %i\n", theFile.good());

	try
	{
		json j;
		theFile >> j;
		printf("%s\n", j.dump().c_str());
		printf("the type is as follows:\n");
		fflush(stdout);

		//Everything will have at least these four
		string type = j["type"];
		
		string modelName = j["model"];

		Model model;
		if (loadedModels.count(modelName) > 0)
		{
			model = loadedModels[path];
		}
		else
		{
			model = Model((thingTitle+"/"+ modelName).c_str());
			loadedModels[path] = model;
		}



		vec3 positionOffset = jsonToVec3(j["positionOffset"]);

		Hitbox hitbox = jsonToHitbox(j["hitbox"]); //TODO: implement hitbox type and jsontohitbox

		//TODO: later attributes might include weight, speed, interactability

		if (type == "agent")
		{
			vec3 cameraOffset = jsonToVec3(j["camera"]["cameraOffset"]);
			vec3 cameraVector = jsonToVec3(j["camera"]["cameraVector"]);

			vec3 gunportOffset = jsonToVec3(j["gunPort"]["gunportOffset"]);
			vec3 gunportVector = jsonToVec3(j["gunPort"]["gunportVector"]);
			//if it's an agent, will have a gunport and a camera
			return new Agent(model, Controller(), hitbox, cameraOffset, cameraVector, gunportOffset, gunportVector);
		}
		else if (type == "object")
		{
			//if it's an object, just make it
		}
		else if (type == "environment")
		{
			//if it's an environment, just make it
		}
		return new Thing();
	}
	catch (exception e)
	{
		printf("error loading model from json:\n%s\nimproper json format, validate using external tool\n%s\n", path.c_str(), e.what());
	}

	return new Thing();

}