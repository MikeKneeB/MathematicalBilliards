#include <cmath>

#include "RectangleTable.h"

RectangleTable::RectangleTable()
{}

RectangleTable::RectangleTable(double x, double y) :
	fX(x), fY(y)
{}

RectangleTable::~RectangleTable()
{}

void RectangleTable::SetX(double x)
{
	if (x > 0) fX = x;

	return;
}

void RectangleTable::SetY(double y)
{
	if (y > 0) fY = y;

	return;
}

double RectangleTable::AngleIncidence(const Vector & collision, const Vector & velocity)
{
	if (collision.fX = fX)
		return M_PI/2 - velocity.Arg();
	else if (collision.fX = -fX)
		return 3*M_PI/2 - velocity.Arg();
	else if (collision.fX = fY)
		return -velocity.Arg();
	else if (collision.fX = -fY)
		return M_PI - velocity.Arg();
}

Vector RectangleTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
	 
}
