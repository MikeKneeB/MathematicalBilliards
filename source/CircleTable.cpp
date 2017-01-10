/**
 * Mike Knee 09/01/2017
 *
 * Source file for the CircleTable class.
 */

#include <cmath>

#include "CircleTable.h"

CircleTable::CircleTable()
{}

CircleTable::CircleTable(double radius) :
	fRadius(radius)
{}

CircleTable::~CircleTable()
{}

double CircleTable::AngleIncidence(const Vector & collision, const Vector & velocity)
{
	//Angle incidence.
	return M_PI - collision.Arg() - velocity.Arg();
}

Vector CircleTable::ReflectVector(const Vector & collision, const Vector & velocity)
{
	//See report for details.
	Vector temp;

	temp = velocity - 2*(velocity.Dot(-collision)*(-collision))/collision.Mod();

	return temp;
}

Vector CircleTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
	//Solve collision point using qaudratic eqn.
	double gamma;

	double a, b, c;

	a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
	b = 2 * (initial.fX * velocity.fX + initial.fY * velocity.fY);
	c = initial.fX * initial.fX + initial.fY * initial.fY - fRadius * fRadius;

	gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

	return initial + gamma * velocity;
}
