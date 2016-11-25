#include "ITable.h"

class EllipseTable : public ITable
{
public:
	EllipseTable();
	EllipseTable(double radius, double xCoef, double yCoef);
	~EllipseTable();

	double GetRadius() const { return fRadius; }
	double GetXCoef()const { return fXCoef; }
	double GetYCoef() const { return fYCoef; }
	void SetRadius(double radius) { if (radius > 0) fRadius = radius; }
	void SetXCoef(double xCoef) {if (xCoef > 0) fXCoef = xCoef; }
	void SetYCoef(double yCoef) {if (yCoef > 0) fYCoef = yCoef; }

	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity);

private:
	double fRadius;
	double fXCoef;
	double fYCoef;
};
