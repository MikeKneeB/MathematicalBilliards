#ifndef _ITABLE_H
#define _ITABLE_H

/**
 * Interface for all billiard tables.
 *
 * Though not mandated, all tables should have a centre at 0,0.
 */

#include "Vector.h"

class ITable
{
public:
	virtual ~ITable() {}

	/**
 	* AngleIncidence returns the angle to rotate the velocity onto the
 	* normal.
 	*/
	virtual double AngleIncidence(const Vector & collision, const Vector & velocity) = 0;

	/**
 	* CollisionPoint returns the point on the table edge that the ball
 	* collides at.
 	*/
	virtual Vector CollisionPoint(const Vector & initial, const Vector & velocity) = 0;
};

#endif
