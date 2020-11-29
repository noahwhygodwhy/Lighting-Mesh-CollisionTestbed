#include "HBS.hpp"

#include "CuboidHitbox.hpp"
#include "CylinderHitbox.hpp"
#include "SphereHitbox.hpp"


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

float getDistance(vec3 a, vec3 b)
{
	float diffx = a.x - b.x;
	float diffy = a.y - b.y;
	float diffz = a.z - b.z;

	return sqrt((diffx * diffx) + (diffy * diffy) + (diffz * diffz));
}

float getDistance(vec2 a, vec2 b)
{
	float diffx = a.x - b.x;
	float diffy = a.y - b.y;

	return sqrt((diffx * diffx) + (diffy * diffy));
}
float getDistance(float x1, float y1, float x2, float y2)
{
	float diffx = x1 - x2;
	float diffy = y1 - y2;
	return sqrt((diffx * diffx) + (diffy * diffy));

}

bool cuboidAndCylinder(CuboidHitbox* hb1, CylinderHitbox* hb2, Thing* t1, Thing* t2, bool correct)
{
	bool toReturn = false;
	vec3 circleCenter = hb2->origin;
	vec3 t1pos = vec3(t1->transform[3]);
	vec3 t2pos = vec3(t2->transform[3]);

	if (getDistance(hb1->origin.x + t1pos.x, hb1->origin.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius ||
		getDistance(hb1->otherCorner.x + t1pos.x, hb1->origin.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius ||
		getDistance(hb1->origin.x + t1pos.x, hb1->otherCorner.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius ||
		getDistance(hb1->otherCorner.x + t1pos.x, hb1->otherCorner.z + t1pos.z, hb2->origin.x + t2pos.x, hb2->origin.z + t2pos.z) < hb2->radius)
	{
		if (!(hb1->otherCorner.y + t1pos.y < hb2->origin.y + t2pos.y || hb1->origin.y + t1pos.y >(hb2->origin.y + t2pos.y + hb2->height)))
		{
			if (correct)
			{
				//TODO: do correction here
			}
			return true;
		}
	}
	return false;
}

bool cuboidAndCuboid(CuboidHitbox* hb1, CuboidHitbox* hb2, Thing* t1, Thing* t2, bool correct)
{

	vec3 t1pos = vec3(t1->transform[3]);
	vec3 t2pos = vec3(t2->transform[3]);
	if (hb1->otherCorner.x+t1pos.x < hb2->origin.x + t2pos.x) return false;
	if (hb1->origin.x + t1pos.x > hb2->otherCorner.x + t2pos.x) return false;
	if (hb1->otherCorner.y + t1pos.y < hb2->origin.y + t2pos.y) return false;
	if (hb1->origin.y + t1pos.y > hb2->otherCorner.y + t2pos.y) return false;
	if (hb1->otherCorner.z + t1pos.z < hb2->origin.z + t2pos.z) return false;
	if (hb1->origin.z + t1pos.z > hb2->otherCorner.z + t2pos.z) return false;
	if (correct)
	{
		//TODO: do correction here
	}
	return true;
}


vector<vec3> getEightCorners(vec3 a, vec3 b)
{
	vec3 originals[] = { a, b };
	vector<vec3> corners;
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < 2; j++)
			{
				corners.push_back(vec3(originals[i].x, originals[i].y, originals[i].z));
			}
		}
	}
}

typedef bool (*radiusChecker)(float a, float b, float r);

bool gt(float a, float b, float r)
{
	return a + r > b;
}
bool lt(float a, float b, float r)
{
	return a-r < b;
}
static radiusChecker ops[][3] = {
	{gt, gt, gt},
	{gt, gt, lt},
	{gt, lt, gt},
	{gt, lt, lt},
	{lt, gt, gt},
	{lt, gt, lt},
	{lt, lt, gt},
	{lt, lt, lt},
};

bool cuboidAndSphere(CuboidHitbox* hb1, SphereHitbox* hb2, Thing* t1, Thing* t2, bool correct)
{
	vec3 a = hb1->origin; //min corner
	vec3 b = hb1->otherCorner; //max corner
	vec3 mid = (a + b) / vec3(2.0f);
	vec3 c = hb2->origin; //c for circle
	float r = hb2->radius;

	/*vec3 nnn = hb1->origin;
	vec3 ppp = hb1->otherCorner;
	vec3 nnp = vec3(nnn.x, nnn.y, ppp.z);
	vec3 npn = vec3(nnn.x, ppp.y, nnn.z);
	vec3 pnn = vec3(ppp.x, nnn.y, nnn.z);
	vec3 pnp = vec3(ppp.x, nnn.y, ppp.z);
	vec3 ppn = vec3(ppp.x, ppp.y, nnn.z);
	vec3 ppp = vec3(ppp.x, ppp.y, ppp.z);*/

	bool x = c.x + r > a.x && c.x - r < b.x;
	bool y = c.y + r > a.y && c.y - r < b.y;
	bool z = c.z + r > a.z && c.z - r < b.z;
	bool posx;
	bool negx;
	bool posy;
	bool negy;
	bool posz;
	bool negz;
	



	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < 2; j++)
			{
				vec3 corner = vec3(originals[i].x, originals[k].y, originals[j].z);
				if (ops[i + k + j][0](hb2->origin.x, originals[i].x, hb2->radius))
				{
				}
				if (ops[i + k + j][1](hb2->origin.y, originals[i].y, hb2->radius))
				{
				}
				if (ops[i + k + j][2](hb2->origin.z, originals[i].z, hb2->radius))
				{

				}
			}
		}
	}


	if (correct)
	{
		//TODO: do correction here
	}
	return true;
}





bool sphereAndSphere(SphereHitbox* hb1, SphereHitbox* hb2, Thing* t1, Thing* t2, bool correct)
{

	vec3 t1pos = vec3(t1->transform[3]);
	vec3 t2pos = vec3(t2->transform[3]);
	if (getDistance(t1pos, t2pos) > hb1->radius + hb2->radius)
	{
		return false;
	}
	if (correct)
	{
		//TODO: do correction here
	}
	return true;
}

bool coliding(Hitbox* hb1, Hitbox* hb2, Thing* t1, Thing* t2, bool correct)
{
	int hbt = (int)hb1->type & (int)hb2->type;

	if (hbt & (int)HitboxType::CUBOID)
	{
		if (hbt & (int)HitboxType::SPHERE)
		{
			if ((int)hb1->type & (int)HitboxType::CUBOID)
				return cuboidAndSphere((CuboidHitbox*)hb1, (SphereHitbox*)hb2, t1, t2, correct);
			return cuboidAndSphere((CuboidHitbox*)hb2, (SphereHitbox*)hb1, t2, t1, correct);

		}
		if (hbt & (int)HitboxType::PLAIN)
		{

		}
		if (hbt & (int)HitboxType::CYLINDER)
		{
			if ((int)hb1->type & (int)HitboxType::CUBOID)
				return cuboidAndCylinder((CuboidHitbox*)hb1, (CylinderHitbox*)hb2, t1, t2, correct);
			return cuboidAndCylinder((CuboidHitbox*)hb2, (CylinderHitbox*)hb1, t2, t1, correct);

		}
		if (hbt & (int)HitboxType::PLLLPP)
		{

		}
		else //both cuboids
		{
			return cuboidAndCuboid((CuboidHitbox*)hb1, (CuboidHitbox*)hb2, t1, t2, correct);
		}
	}
	if (hbt & (int)HitboxType::SPHERE)
	{
		return sphereAndSphere((SphereHitbox*) hb1, (SphereHitbox*) hb2, t1, t2, correct);
	}
	return false;
	//TODO: eventually this will have to include how to handle all of the types of hitboxes. Is there a better way of doing this besides each pairs?
}




//TODO: IT"S NOT HANDLING ROTATED CUBOIDS :|||||||||||||||||||||||||||||||||||

static int tasdf = 0;

vector<IThing*> general(vector<IThing*> things, IThing* specificThing)
{
	vec3 dump;
	vec3 maxs = ((Thing*)specificThing)->maxs;//TODO:
	vec3 mins = ((Thing*)specificThing)->mins;
	vector<IThing*> generalAreaThings;
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
	return generalAreaThings;
}
vector<IThing*> broad(vector<IThing*> things, IThing* specificThing)
{

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
				if (coliding(hb1, hb2, (Thing*)things.at(i), (Thing*)specificThing, false))
				{
					maybeTouching.push_back(things.at(i));
					shouldBreak = true;
					break;
				}
			}
		}
	}
	return maybeTouching;
}
bool narrow(vector<IThing*> things, IThing* specificThing)
{

	for (IThing* mtThing : things)
	{
		if (mtThing == specificThing)
		{
			continue;
		}
		for (auto hb1 : ((Thing*)mtThing)->generalHitbox) //for each hitbox in the first thing
		{
			for (auto hb2 : ((Thing*)specificThing)->generalHitbox) //for each hitbox in the second thing
			{
				if (coliding(hb1, hb2, (Thing*)mtThing, (Thing*)specificThing, true))
				{
					printf("%i THEY'RE COLLIDING\n", tasdf++);
					//TODO:make the correction
					return true;
				}
			}
		}
	}
	return false;
}

void handleHits(vector<IThing*> things, IThing* specificThing)
{

	//definetly optimize better later^tm
	

	vector<IThing*> generalAreaThings = general(things, specificThing);

	vector<IThing*> maybeTouching = broad(generalAreaThings, specificThing);

	while (narrow(maybeTouching, specificThing))
	{

	}
	//printf("match: %p\n", maybeTouching.at(0));
	//create a list of definitely touching things, and find out by how much
}





