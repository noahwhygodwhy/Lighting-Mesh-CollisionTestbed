#ifndef RECT_HITBOX_H
#define RECT_HITBOX_H

#include "PrimativeHitbox.hpp"

class RectHitbox : PrimativeHitbox
{
public:
	RectHitbox(vec3 origin, float x, float y, float z);
	~RectHitbox();

private:

};
#endif