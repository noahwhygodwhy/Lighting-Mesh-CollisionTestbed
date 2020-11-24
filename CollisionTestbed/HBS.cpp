#include "HBS.hpp"

#include "CuboidHitbox.hpp"

void handleHits(vector<IThing*> things)
{

	//definetly optimize better later^tm
	vector<pair<Thing*, Thing*>> maybeTouching;
	vec3 dump;
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
}





bool coliding(Hitbox hb1, Hitbox hb2, vec3* correction)
{
	if (hb1.type == hb2.type)
	{
		
	}

	if (hb1.type == HitboxType::CUBOID & hb2.type == HitboxType::CUBOID) 
	{
		CuboidHitbox chb1 = *(CuboidHitbox*)&hb1;
		CuboidHitbox chb2 = *(CuboidHitbox*)&hb2;
	}
}
