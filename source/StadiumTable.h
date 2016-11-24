#ifndef _STADIUMTABLE_H
#define _STADIUMTABLE_H

#include "ITable.h"

class StadiumTable : public ITable
{
public:
	StadiumTable();
	StadiumTable(double x, double y);
	~StadiumTable();

	double GetX() const { return fX; }
	double GetY() const { return fY; }
	void SetX(double x);
	void SetY(double y); 

	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity);	
private:
	double fX;
	double fY;
};

#endif
