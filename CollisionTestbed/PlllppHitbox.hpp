#ifndef PLLLPPHITBOX_H
#define PLLLPPHITBOX_H

#include "Hitbox.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//https://en.wikipedia.org/wiki/Parallelepiped
class PlllppHitbox : Hitbox
{
public:
	PlllppHitbox(vec3 origin, vec3 a, vec3 b, vec3 c);
	~PlllppHitbox();

private:
	vec3 a;
	vec3 b;
	vec3 c;
};


#endif