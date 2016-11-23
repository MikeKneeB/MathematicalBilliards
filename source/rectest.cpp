#include <cstdio>

#include "RectangleTable.h"

int main()
{
	RectangleTable rec = RectangleTable(1,1);

	Vector initial = Vector(0,0);
	Vector velocity = Vector(1,1);

	Vector pos;
	double angle;

	pos = rec.CollisionPoint(initial, velocity);
	angle = rec.AngleIncidence(pos, velocity);

	printf("%f, %f\n", pos.fX, pos.fY);
	printf("%f\n", velocity.Arg());
	printf("%f\n", angle);

	return 0;
}
