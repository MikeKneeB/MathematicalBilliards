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
	if (collision.fX == fX)
		return -velocity.Arg();
	else if (collision.fX == -fX)
		return M_PI - velocity.Arg();
	else if (collision.fX == fY)
		return M_PI/2 - velocity.Arg();
	else if (collision.fX == -fY)
		return 3*M_PI/2 - velocity.Arg();
	else return 0;
}

Vector RectangleTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
	double gamma;

	if (velocity.fY >= 0)
	{
		//p = i + gv
		gamma = (fY - initial.fY)/velocity.fY;
		double x = initial.fX + gamma * velocity.fX;
		if (x <= fX && x >= -fX)
		{
			return Vector(x, fY);
		}
	}
	else
	{
		gamma = (-fY - initial.fY)/velocity.fY;
		double x = initial.fX + gamma * velocity.fX;
		if (x <= fX && x >= -fX)
		{
			return Vector(x, -fY);
		}
	}

	if (velocity.fX >= 0)
	{
		gamma = (fX - initial.fX)/velocity.fX;
		double y = initial.fY + gamma * velocity.fY;
		return Vector(fX, y);
	}
	else
	{
		gamma = (-fX - initial.fX)/velocity.fX;
		double y = initial.fY + gamma * velocity.fY;
		return Vector(-fX, y);
	}

	return Vector(0,0);
}
