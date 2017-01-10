/**
 * Mike Knee 09/01/2017
 *
 * Header file for the CircleTable class.
 */

#ifndef _CIRCLETABLE_H
#define _CIRCLETABLE_H

#include "ITable.h"

/**
 * Circular billiards table class. Inherits from ITable. 
 */
class CircleTable : public ITable
{
public:
	/**
	 * Empty constructor, does not initialise with default values.
	 */
	CircleTable();
	/**
	 * Constructor with radius defined.
	 */
	CircleTable(double radius);
	/**
	 * Destructor does nothing.
	 */
	~CircleTable();

	// Getters and setters.
	inline double GetRadius() { return fRadius; }
	inline void SetRadius(double radius) { if (radius > 0) fRadius = radius; }

	// Functions implemented from ITable.
	double AngleIncidence(const Vector & collision, const Vector & velocity);
	Vector ReflectVector(const Vector & collision, const Vector & velocity);
	Vector CollisionPoint(const Vector & initial, const Vector & velocity); 
private:
	// Circular table is parameterised by a radius, and has centre at
	// (0,0).
	double fRadius;
};

#endif
