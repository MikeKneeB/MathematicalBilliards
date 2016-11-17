#include "Vector.h"

class ITable
{
public:
	virtual ~ITable() {}
	virtual double AngleIncidence(const Vector & initial, const Vector & velocity) = 0;
	virtual Vector CollisionPoint(const Vector & initial, const Vector & velocity) = 0;
};
