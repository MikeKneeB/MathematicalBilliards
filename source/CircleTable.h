#include "ITable.h"

class CircleTable : public ITable
{
public:
	CircleTable();
	CircleTable(double radius);
	~CircleTable();

	inline double GetRadius() { return fRadius; }
	inline void SetRadius(double radius) { fRadius = radius; }

	double AngleIncidence(const Vector & initial, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity); 
private:
	double fRadius;
}
