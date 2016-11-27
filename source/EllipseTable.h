#ifndef _ELLIPSETABLE_H
#define _ELLIPSETABLE_H

#include "ITable.h"

/**
 * Elliptical billiard table class. Inherits from ITable.
 */
class EllipseTable : public ITable
{
public:
	/**
	 * Empty constructor. Does not initialise values. 
	 */
	EllipseTable();
	/**
	 * Constructor which initialises parameters.
	 */
	EllipseTable(double radius, double xCoef, double yCoef);
	/**
	 * Destructor, does nothing.
	 */
	~EllipseTable();

	// Getters and setters.
	double GetRadius() const { return fRadius; }
	double GetXCoef()const { return fXCoef; }
	double GetYCoef() const { return fYCoef; }
	void SetRadius(double radius) { if (radius > 0) fRadius = radius; }
	void SetXCoef(double xCoef) {if (xCoef > 0) fXCoef = xCoef; }
	void SetYCoef(double yCoef) {if (yCoef > 0) fYCoef = yCoef; }

	// Implemented from ITable.
	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity);

private:
	// Ellipse parameters.
	double fRadius;
	double fXCoef;
	double fYCoef;
};

#endif
