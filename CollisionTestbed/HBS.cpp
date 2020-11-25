#include "HBS.hpp"

#include "CuboidHitbox.hpp"
#include "CylinderHitbox.hpp"



bool generalArea(vec3 t1pos, vec3 t2pos, vec3 origMax, vec3 origMin, vec3 otherMax, vec3 otherMin)
{
	origMax += t1pos;
	origMin += t1pos;
	otherMax += t2pos;
	otherMin += t2pos;
	//printf("origMax %f, %f, %f\n", origMax.x, origMax.y, origMax.z);
	//printf("origMin %f, %f, %f\n", origMin.x, origMin.y, origMin.z);
	//printf("otherMax %f, %f, %f\n", otherMax.x, otherMax.y, otherMax.z);
	//printf("otherMin %f, %f, %f\n", otherMin.x, otherMin.y, otherMin.z);
	if (origMax.x < otherMin.x) return false;
	if (origMin.x > otherMax.x) return false;
	if (origMax.y < otherMin.y) return false;
	if (origMin.y > otherMax.y) return false;
	if (origMax.z < otherMin.z) return false;
	if (origMin.z > otherMax.z) return false;
	return true;
}

float getDistance(float x1, float y1, float x2, float y2)
{
	float diffx = x1 - x2;
	float diffy = y1 - y2;
	return sqrt((diffx * diffx) + (diffy * diffy));

}

bool cuboidAndCylinder(CuboidHitbox* hb1, CylinderHitbox* hb2, vec3 t1pos, vec3 t2pos, vec3* correction)
{
	vec3 circleCenter = hb2->origin;

	if (getDistance(hb1->origin.x + t1pos.x, hb1->origin.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius ||
		getDistance(hb1->otherCorner.x + t1pos.x, hb1->origin.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius ||
		getDistance(hb1->origin.x + t1pos.x, hb1->otherCorner.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius ||
		getDistance(hb1->otherCorner.x + t1pos.x, hb1->otherCorner.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius)
	{
		if (hb1->otherCorner.y + t1pos.y < hb2->origin.y + t2pos.y || hb1->origin.y + t1pos.y >(hb2->origin.y + t2pos.y + hb2->height))
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

bool cuboidAndCuboid(CuboidHitbox* hb1, CuboidHitbox* hb2, vec3 t1pos, vec3 t2pos, vec3* correction)
{

	if (hb1->otherCorner.x+t1pos.x < hb2->origin.x + t2pos.x) return false;
	if (hb1->origin.x + t1pos.x > hb2->otherCorner.x + t2pos.x) return false;
	if (hb1->otherCorner.y + t1pos.y < hb2->origin.y + t2pos.y) return false;
	if (hb1->origin.y + t1pos.y > hb2->otherCorner.y + t2pos.y) return false;
	if (hb1->otherCorner.z + t1pos.z < hb2->origin.z + t2pos.z) return false;
	if (hb1->origin.z + t1pos.z > hb2->otherCorner.z + t2pos.z) return false;
	//TODO: need to calculate correction
	return true;
}

bool coliding(Hitbox* hb1, Hitbox* hb2, vec3 t1pos, vec3 t2pos, vec3* correction)
{
	int hbt = (int)hb1->type & (int)hb2->type;

	if (hbt & (int)HitboxType::CUBOID)
	{
		if (hbt & (int)HitboxType::PLAIN)
		{

		}
		if (hbt & (int)HitboxType::CYLINDER)
		{
			if ((int)hb1->type & (int)HitboxType::CUBOID)
				return cuboidAndCylinder((CuboidHitbox*)hb1, (CylinderHitbox*)hb2, t1pos, t2pos, correction);
			return cuboidAndCylinder((CuboidHitbox*)hb2, (CylinderHitbox*)hb1,t2pos, t1pos, correction);

		}
		if (hbt & (int)HitboxType::PLLLPP)
		{

		}
		else //both cuboids
		{
			return cuboidAndCuboid((CuboidHitbox*)hb1, (CuboidHitbox*)hb2, t1pos, t2pos, correction);
		}
	}
	return false;
	//TODO: eventually this will have to include how to handle all of the types of hitboxes. Is there a better way of doing this besides each pairs?
}




//TODO: IT"S NOT HANDLING ROTATED CUBOIDS :|||||||||||||||||||||||||||||||||||

static int tasdf = 0;

void handleHits(vector<IThing*> things, IThing* specificThing)
{

	//definetly optimize better later^tm
	vec3 dump;

	vec3 maxs = ((Thing*)specificThing)->maxs;//TODO:
	vec3 mins = ((Thing*)specificThing)->mins;

	vector<IThing*> generalAreaThings;

	//printf("things:\n");
	
	//create a list of general area things
	for (int i = 0; i < things.size(); i++)
	{
		if (things.at(i) == specificThing)
		{
			continue;
		}
		vec3 thingmaxs = ((Thing*)things.at(i))->maxs;
		vec3 thingmins = ((Thing*)things.at(i))->mins;
		if (generalArea(vec3(((Thing*)specificThing)->transform[3]), vec3(((Thing*)things.at(i))->transform[3]), maxs, mins, thingmaxs, thingmins))
		{
			generalAreaThings.push_back(things.at(i));
		}
	}
	//printf("match: %p\n", generalAreaThings.at(0));

	//create a list of maybe touching things
	vector<IThing*> maybeTouching;
	for (int i = 0; i < things.size(); i++)
	{
		if (things.at(i) == specificThing)
		{
			continue;
		}
		bool shouldBreak = false;
		for (auto hb1 : ((Thing*)things.at(i))->generalHitbox) //for each hitbox in the first thing
		{
			if (shouldBreak)
			{
				break;
			}
			for (auto hb2 : ((Thing*)specificThing)->generalHitbox) //for each hitbox in the second thing
			{
				if (coliding(hb1, hb2, vec3(((Thing*)things.at(i))->transform[3]), vec3(((Thing*)specificThing)->transform[3]), &dump))
				{
					maybeTouching.push_back(things.at(i));
					shouldBreak = true;
					break;
				}
			}
		}
	}
	//printf("match: %p\n", maybeTouching.at(0));
	//create a list of definitely touching things, and find out by how much
	vec3 byHowMuch;
	for (IThing* mtThing : maybeTouching)
	{
		if (mtThing == specificThing)
		{
			continue;
		}
		bool shouldBreak = false;
		for (auto hb1 : ((Thing*)mtThing)->generalHitbox) //for each hitbox in the first thing
		{
			if (shouldBreak)
			{
				break;
			}
			for (auto hb2 : ((Thing*)specificThing)->generalHitbox) //for each hitbox in the second thing
			{
				if (coliding(hb1, hb2, vec3(((Thing*)mtThing)->transform[3]), vec3(((Thing*)specificThing)->transform[3]), &byHowMuch))
				{
					printf("%i THEY'RE COLLIDING\n", tasdf++);
					//TODO:make the correction
					shouldBreak = true;
					break;
				}
			}
		}
	}
}





