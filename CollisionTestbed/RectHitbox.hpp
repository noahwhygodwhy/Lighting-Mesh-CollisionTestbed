#ifndef RECT_HITBOX_H
#define RECT_HITBOX_H

#include "PrimativeHitbox.hpp"

class RectHitbox : public PrimativeHitbox
{
public:
	RectHitbox(vec3 origin, vec3 dims);
	~RectHitbox();

private:

};
#endif