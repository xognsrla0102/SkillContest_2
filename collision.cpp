#include "DXUT.h"
#include "collision.h"

BOOL AABB(RECT obj1, RECT obj2)
{
	RECT rt;
	return IntersectRect(&rt, &obj1, &obj2);
}
