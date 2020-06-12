#include "DXUT.h"
#include "math.h"
#include "math.h"

double DistPoint(VEC2 a, VEC2 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

VEC2 RandomInsideSquare()
{
	return VEC2(rand() % 6 / 10.f * (rand() % 2 ? 1 : -1), rand() % 6 / 10.f * (rand() % 2 ? 1 : -1));
}
