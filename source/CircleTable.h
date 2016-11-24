#ifndef _CIRCLETABLE_H
#define _CIRCLETABLE_H

#include "ITable.h"

class CircleTable : public ITable
{
public:
	CircleTable();
	CircleTable(double radius);
	~CircleTable();

	inline double GetRadius() { return fRadius; }
	inline void SetRadius(double radius) { if (radius > 0) fRadius = radius; }

	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity); 
private:
	double fRadius;
};

#endif
