#include "HBS.hpp"

#include "CuboidHitbox.hpp"
#include "CylinderHitbox.hpp"



bool generalArea(vec3 origMax, vec3 origMin, vec3 otherMax, vec3 otherMin)
{
	if (origMax.x < otherMin.x) return false;
	if (origMin.x > otherMax.x) return false;
	if (origMax.y < otherMin.y) return false;
	if (origMin.y > otherMax.y) return false;
	if (origMax.z < otherMin.z) return false;
	if (origMin.z > otherMax.z) return false;
	return true;
}



//TODO: IT"S NOT HANDLING ROTATED CUBOIDS :|||||||||||||||||||||||||||||||||||


void handleHits(vector<IThing*> things, IThing* specificThing)
{

	//definetly optimize better later^tm
	vec3 dump;

	vec3 maxs = ((Thing*)specificThing)->maxs;//TODO:
	vec3 mins = ((Thing*)specificThing)->mins;

	vector<IThing*> generalAreaThings;

	//create a list of general area things
	for (int i = 0; i < things.size(); i++)
	{
		vec3 thingmaxs = ((Thing*)things.at(i))->maxs;
		vec3 thingmins = ((Thing*)things.at(i))->mins;
		if (generalArea(maxs, mins, thingmaxs, thingmins))
		{
			generalAreaThings.push_back(things.at(i));
		}
	}

	//create a list of maybe touching things
	vector<IThing*> maybeTouching;
	for (int i = 0; i < things.size(); i++)
	{
		bool shouldBreak = false;
		for (auto hb1 : ((Thing*)things.at(i))->generalHitbox) //for each hitbox in the first thing
		{
			if (shouldBreak)
			{
				break;
			}
			for (auto hb2 : ((Thing*)specificThing)->generalHitbox) //for each hitbox in the second thing
			{
				if (coliding(hb1, hb2, &dump))
				{
					maybeTouching.push_back(things.at(i));
					shouldBreak = true;
					break;
				}
			}
		}
	}
	//create a list of definitely touching things, and find out by how much
	vec3 byHowMuch;
	for (IThing* mtThing : maybeTouching)
	{
		bool shouldBreak = false;
		for (auto hb1 : ((Thing*)mtThing)->generalHitbox) //for each hitbox in the first thing
		{
			if (shouldBreak)
			{
				break;
			}
			for (auto hb2 : ((Thing*)specificThing)->generalHitbox) //for each hitbox in the second thing
			{
				if (coliding(hb1, hb2, &byHowMuch))
				{
					printf("THEY'RE COLLIDING\n");
					//TODO:make the correction
					shouldBreak = true;
					break;
				}
			}
		}
	}
}







float getDistance(float x1, float y1, float x2, float y2)
{
	float diffx = x1 - x2;
	float diffy = y1 - y2;
	return sqrt((diffx * diffx) + (diffy * diffy));

}

bool cuboidAndCylinder(CuboidHitbox* hb1, CylinderHitbox* hb2, vec3* correction)
{
	vec3 circleCenter = hb2->origin;
	
	if (getDistance(hb1->origin.x, hb1->origin.z, hb2->origin.x, hb2->origin.z) < hb2->radius ||
		getDistance(hb1->otherCorner.x, hb1->origin.z, hb2->origin.x, hb2->origin.z) < hb2->radius ||
		getDistance(hb1->origin.x, hb1->otherCorner.z, hb2->origin.x, hb2->origin.z) < hb2->radius ||
		getDistance(hb1->otherCorner.x, hb1->otherCorner.z, hb2->origin.x, hb2->origin.z) < hb2->radius)
	{
		if (hb1->otherCorner.y < hb2->origin.y || hb1->origin.y >(hb2->origin.y + hb2->height))
		{
			return false;
		}
		else
		{
			return true;
			//it's colliding, by how much, that's for you to find out
		}
		//we know x/z is in, now just check y;
	}
	

	return false;
}

bool cuboidAndCuboid(CuboidHitbox* hb1, CuboidHitbox* hb2, vec3* correction)
{
	if (hb1->otherCorner.x < hb2->origin.x) return false;
	if (hb1->origin.x > hb2->otherCorner.x) return false;
	if (hb1->otherCorner.y < hb2->origin.y) return false;
	if (hb1->origin.y > hb2->otherCorner.y) return false;
	if (hb1->otherCorner.z < hb2->origin.z) return false;
	if (hb1->origin.z > hb2->otherCorner.z) return false;
	//TODO: need to calculate correction
	return true;
}

bool coliding(Hitbox* hb1, Hitbox* hb2, vec3* correction)
{
	int hbt = (int) hb1->type & (int) hb2->type;

	if (hbt & (int)HitboxType::CUBOID)
	{
		if (hbt & (int)HitboxType::PLAIN)
		{

		}
		if (hbt & (int)HitboxType::CYLINDER)
		{
			if ((int)hb1->type & (int)HitboxType::CUBOID)
				return cuboidAndCylinder((CuboidHitbox*)hb1, (CylinderHitbox*)hb2, correction);
			return cuboidAndCylinder((CuboidHitbox*)hb2, (CylinderHitbox*)hb1, correction);
				
		}
		if (hbt & (int)HitboxType::PLLLPP)
		{

		}
		else //both cuboids
		{
			return cuboidAndCuboid((CuboidHitbox*)hb1, (CuboidHitbox*)hb2, correction);
		}
	}
	return false;
	//TODO: eventually this will have to include how to handle all of the types of hitboxes. Is there a better way of doing this besides each pairs?
}
