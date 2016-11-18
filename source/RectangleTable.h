#ifndef _SQAURETABLE_H
#define _SQAURETABLE_H

#include "ITable.h"

class RectangleTable : public ITable
{
public:
	RectangleTable();
	RectangleTable(double x, double y);
	~RectangleTable();

	double GetX() const { return fX; }
	double GetY() const { return fY; }
	void SetX();
	void SetY();

	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity); 
private:
	double fX;
	double fY;
};

#endif
