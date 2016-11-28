#ifndef _STADIUMTABLE_H
#define _STADIUMTABLE_H

#include "ITable.h"

/**
 * Stadium billiards table, inherits from ITable.
 */
class StadiumTable : public ITable
{
public:
	/**
	 * Empty constructor, does not initiiase member variables.
	 */
	StadiumTable();
	/**
	 * Constructor for stadium table with geometry fX = x and fY = y. This
	 * results in a table with width 2y, and maximum length 2x + 2y. The
	 * semicircles at each end have radius y.
	 */
	StadiumTable(double x, double y);
	/**
	 * Empty destrcutor.
	 */
	~StadiumTable();

	// Getters and setters.
	double GetX() const { return fX; }
	double GetY() const { return fY; }
	void SetX(double x);
	void SetY(double y); 

	// Functions implemented from ITable.
	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity);	
private:
	// Member variables describing geometry of the stadium billiards table.
	double fX;
	double fY;
};

#endif
