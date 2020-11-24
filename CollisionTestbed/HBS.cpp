#include "HBS.hpp"

#include "CuboidHitbox.hpp"
#include "CylinderHitbox.hpp"

void handleHits(vector<IThing*> things, IThing* specificThing)
{

	//definetly optimize better later^tm
	vector<pair<Thing*, Thing*>> maybeTouching;
	vec3 dump;

	vec3 maxs = ((Thing*)specificThing)->getMaxs();//TODO:
	vec3 mins = ((Thing*)specificThing)->getMins();




	for (int i = 0; i < things.size(); i++)//for each thing
	{
		for (int j = i + 1; j < things.size(); j++)//for each other thing to that thing that hasn't already been done
		{
			bool shouldBreak = false;
			for (auto hb1 : ((Thing*)things.at(i))->generalHitbox) //for each hitbox in the first thing
			{
				if (shouldBreak)
				{
					break;
				}
				for (auto hb2 : ((Thing*)things.at(j))->generalHitbox) //for each hitbox in the second thing
				{
					if (coliding(hb1, hb2, &dump))
					{
						maybeTouching.push_back(pair((Thing*)things.at(i), (Thing*)things.at(j)));
						shouldBreak = true;
						break;
					}
				}
			}
		} 
	}
	for (pair<Thing*, Thing*> things : maybeTouching)
	{
		for (auto hb1 : ((Thing*)things.first)->preciseHitbox)
		{

		}
	}
}








bool cuboidAndCylinder(CuboidHitbox hb1, CylinderHitbox hb2, vec3* correction)
{

}

bool cuboidAndCuboid(CuboidHitbox hb1, CuboidHitbox hb2, vec3* correction)
{
	//i would really read the book before starting
}

bool coliding(Hitbox hb1, Hitbox hb2, vec3* correction)
{
	int hbt = (int) hb1.type & (int) hb2.type;

	if (hbt & (int)HitboxType::CUBOID)
	{
		if (hbt & (int)HitboxType::PLAIN)
		{

		}
		if (hbt & (int)HitboxType::CYLINDER)
		{
			if ((int)hb1.type & (int)HitboxType::CUBOID)
				return cuboidAndCylinder(*(CuboidHitbox*)&hb1, *(CylinderHitbox*)&hb2, correction);
			return cuboidAndCylinder(*(CuboidHitbox*)&hb2, *(CylinderHitbox*)&hb1, correction);
				
		}
		if (hbt & (int)HitboxType::PLLLPP)
		{

		}
		else //both cuboids
		{
			return cuboidAndCuboid(*(CuboidHitbox*)&hb1, *(CuboidHitbox*)&hb2, correction);
		}
	}
	return false;
	//TODO: eventually this will have to include how to handle all of the types of hitboxes. Is there a better way of doing this besides each pairs?
}
