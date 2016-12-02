#include "ITable.h"

class LorentzTable : public ITable
{
	LorentzTable();
	LorentzTable(double x, double y, double radius);
	~LorentzTable();

	double GetX() const { return fX; } 
	double GetY() const { return fY; }
	double GetRadius() const { return fRadius; }
	void SetX(double x);
	void SetY(double y);
	void SetRadius(double radius);

	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity);

private:
	double fX;
	double fY;
	double fRadius;	
};
