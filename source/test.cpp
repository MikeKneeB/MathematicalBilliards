#include <cstdio>

#include "CircleTable.h"

int main()
{
	CircleTable table = CircleTable(1);

	Vector initial = Vector(0,0.5);
	Vector velocity = Vector(1,1);
	
	Vector collision = table.CollisionPoint(initial, velocity);

	printf("%f, %f\n", collision.fX, collision.fY);
	printf("%f\n", table.AngleIncidence(collision, velocity));

	return 0;
}
