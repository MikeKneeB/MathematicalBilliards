#include <cmath>

#include "StadiumTable.h"

StadiumTable::StadiumTable()
{}

StadiumTable::StadiumTable(double x, double y) :
	fX(x), fY(y)
{}

StadiumTable::~StadiumTable()
{}

void StadiumTable::SetX(double x)
{
	if (x > 0) fX = x;

	return;
}

void StadiumTable::SetY(double y)
{
	if (y > 0) fY = y;

	return;
}

double StadiumTable::AngleIncidence(const Vector & collision, const Vector & velocity)
{
	Vector norm = Vector(0,0);
	double temp;

	if (collision.fY == fY)
		norm = Vector(0,-1);
	else if (collision.fY == -fY)
		norm = Vector(0,1);
	else if (collision.fX >= fX)
	{
		norm = collision - Vector(fX, 0);		
		norm = norm/norm.Mod();
	}
	else if (collision.fX <= -fX)
	{
		norm = collision - Vector(-fX, 0);
		norm = norm/norm.Mod();
	}

	temp = norm.Arg() - velocity.Arg();
	return temp;
}

Vector StadiumTable::ReflectVector(const Vector & collision, const Vector & velocity)
{
	Vector norm = Vector(0,0);
	Vector temp;

	if (collision.fY == fY)
		norm = Vector(0,-1);
	else if (collision.fY == -fY)
		norm = Vector(0,1);
	else if (collision.fX >= fX)
	{
		norm = collision - Vector(fX, 0);		
		norm = -norm/norm.Mod();
	}
	else if (collision.fX <= -fX)
	{
		norm = collision - Vector(-fX, 0);
		norm = -norm/norm.Mod();
	}

	temp = velocity - 2*velocity.Dot(norm)*norm;
	return temp;
}

Vector StadiumTable::CollisionPoint(const Vector & initial, const Vector & velocity)
{
	double gamma;
	Vector temp;

	if (velocity.fY > 0)
	// Set y = fY:
	{
		//p = i + gv
		gamma = (fY - initial.fY)/velocity.fY;
		double x = initial.fX + gamma * velocity.fX;
		if (x <= fX && x >= -fX)
		{
			return Vector(x, fY);
		}
		else if (x >= fX)
		{
			if (initial.fX >= fX)
			{
				temp = initial - Vector(fX,0);

				double a, b, c;

				a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
				b = 2 * (temp.fX * velocity.fX + temp.fY * velocity.fY);
				c = temp.fX * temp.fX + temp.fY * temp.fY - fY * fY;

				gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

				return temp + gamma * velocity + Vector(fX,0);
			}
		}
		else if (x <= -fX)
		{
			if (initial.fX <= -fX)
			{
				temp = initial - Vector(-fX,0);

				double a, b, c;

				a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
				b = 2 * (temp.fX * velocity.fX + temp.fY * velocity.fY);
				c = temp.fX * temp.fX + temp.fY * temp.fY - fY * fY;

				gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

				return temp + gamma * velocity + Vector(-fX,0);

			}
		}
	}
	else if (velocity.fY < 0)
	// Set y = -fY:
	{
		gamma = (-fY - initial.fY)/velocity.fY;
		double x = initial.fX + gamma * velocity.fX;
		if (x <= fX && x >= -fX)
		{
			return Vector(x, -fY);
		}
		else if (x >= fX)
		{
			if (initial.fX >= fX)
			{
				temp = initial - Vector(fX,0);

				double a, b, c;

				a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
				b = 2 * (temp.fX * velocity.fX + temp.fY * velocity.fY);
				c = temp.fX * temp.fX + temp.fY * temp.fY - fY * fY;

				gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

				return temp + gamma * velocity + Vector(fX,0);
			}
		}
		else if (x <= -fX)
		{
			if (initial.fX <= -fX)
			{
				temp = initial - Vector(-fX,0);

				double a, b, c;

				a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
				b = 2 * (temp.fX * velocity.fX + temp.fY * velocity.fY);
				c = temp.fX * temp.fX + temp.fY * temp.fY - fY * fY;

				gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

				return temp + gamma * velocity + Vector(-fX,0);

			}
		}
	}

	// Setting y = fY has gone out of bounds, so now set x = fX:
	if (velocity.fX > 0)
	// x = fX:
	{
		gamma = (fX - initial.fX)/velocity.fX;
		double y = initial.fY + gamma * velocity.fY;
		temp = Vector(0,y);

		double a, b, c;

		a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
		b = 2 * (/*temp.fX * velocity.fX + */temp.fY * velocity.fY);
		c = /*temp.fX * temp.fX + */temp.fY * temp.fY - fY * fY;

		gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

		return temp + gamma * velocity + Vector(fX, 0);

	}
	else if (velocity.fX < 0)
	// x = -fX:
	{
		gamma = (-fX - initial.fX)/velocity.fX;
		double y = initial.fY + gamma * velocity.fY;
		temp = Vector(0,y);
	
		double a, b, c;

		a = velocity.fX * velocity.fX + velocity.fY * velocity.fY;
		b = 2 * (/*temp.fX * velocity.fX + */temp.fY * velocity.fY);
		c = /*temp.fX * temp.fX + */temp.fY * temp.fY - fY * fY;

		gamma = (-b + std::sqrt(b * b - 4 * a * c))/(2 * a);

		return temp + gamma * velocity + Vector(-fX, 0);
	}

	return Vector(0,0);
}
