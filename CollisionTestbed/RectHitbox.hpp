#ifndef RECT_HITBOX_H
#define RECT_HITBOX_H

#include "PrimativeHitbox.hpp"

class RectHitbox : PrimativeHitbox
{
public:
	RectHitbox(vec3 origin, float dim1, float dim2, float dim3);
	~RectHitbox();

private:

};
#endif