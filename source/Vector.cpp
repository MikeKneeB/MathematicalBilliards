#include "Vector.h"

#include <cmath>

Vector::Vector()
{}

Vector::Vector(double x, double y) :
	fX(x), fY(y)
{}

Vector::Vector(const Vector & other) :
	fX(other.fX), fY(other.fY)
{}

Vector::~Vector()
{}

double Vector::Dot(const Vector & other)
{
	return fX * other.fX + fY * other.fY;
}

double Vector::Arg()
{
	return std::atan(fY/fX);
}

double Vector::Mod()
{
	return std::sqrt(fX * fX + fY * fY);
}

double Vector::Norm()
{
	return Vector(fX / this->Mod(), fY / this->Mod());
}
