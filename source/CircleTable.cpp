#include <cmath>

#include "CircleTable.h"
#include "BilliardExcept.h"

CircleTable::CircleTable()
{}

CircleTable::CircleTable(double radius) :
	fRadius(radius)
{}

CircleTable::~CircleTable()
{}

double CircleTable::AngleIncidence(const Vector & collision, const Vector & velocity)
{
//	if (collision.Mod() != fRadius)
//	{
//		not_collision_exception e;
//		throw e;
//	}
	return collision.Arg() - velocity.Arg();
}

Vector CircleTable::ReflectVector(const Vector & collision, const Vector & velocity)
{
	Vector temp;

	temp = velocity - 2*(velocity.Dot(-collision)*(-collision))/collision.Mod();

	return temp;
}

Vector CircleTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
//	if (initial.Mod() > fRadius)
//	{
//		out_of_bounds_exception e;
//		throw e;
//	}
		
	double gamma;

	double a, b, c;

	a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
	b = 2 * (initial.fX * velocity.fX + initial.fY * velocity.fY);
	c = initial.fX * initial.fX + initial.fY * initial.fY - fRadius * fRadius;

	gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

	return initial + gamma * velocity;
}
