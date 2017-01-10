/**
 * Mike Knee 09/01/2017
 *
 * Source file for the EllipseTable class.
 */

#include <cmath>

#include "EllipseTable.h"

EllipseTable::EllipseTable()
{}

EllipseTable::EllipseTable(double radius, double xCoef, double yCoef) :
	fRadius(radius), fXCoef(xCoef), fYCoef(yCoef)
{}

EllipseTable::~EllipseTable()
{}

double EllipseTable::AngleIncidence(const Vector & collision, const Vector & velocity)
{
	double theta;

	//Standard ellipse angle formula.
	theta = std::atan((collision.fY * fXCoef * fXCoef)/(collision.fX * fYCoef * fYCoef));

	return M_PI - theta - velocity.Arg();
}

Vector EllipseTable::ReflectVector(const Vector & collision, const Vector & velocity)
{
	double theta;

	//Ellipse surface normal.
	theta = std::atan((collision.fY * fXCoef * fXCoef)/(collision.fX * fYCoef * fYCoef));

	//Use this for normal vector:
	Vector norm = Vector(std::cos(theta), std::sin(theta));

	//Calc:
	return velocity - 2*velocity.Dot(norm)*norm;
}

Vector EllipseTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
	//Solve using quadratic eqn.
	double gamma;

	double a, b, c;

	a = velocity.fX * velocity.fX + fXCoef * fXCoef * velocity.fY * velocity.fY / (fYCoef * fYCoef);
	b = 2 * (initial.fX * velocity.fX + fXCoef * fXCoef * initial.fY * velocity.fY / (fYCoef * fYCoef));
	c = initial.fX * initial.fX + fXCoef * fXCoef * initial.fY * initial.fY / (fYCoef * fYCoef) - fXCoef * fXCoef * fRadius * fRadius;

	gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

	//p = i + gv
	return initial + gamma * velocity;

}
