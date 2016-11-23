#ifndef _BILLIARDEXCEPT_H
#define _BILLIARDEXCEPT_H

#include <exception>

class out_of_bounds_exception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Position is outside table.\n";
	}
};

class not_collision_exception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Position is not a collision.\n";
	}
};

#endif
