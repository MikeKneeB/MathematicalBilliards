#ifndef _VECTOR_H
#define _VECTOR_H

class Vector
{
public:
	Vector();
	Vector(double x, double y);
	Vector(const Vector & other);
	~Vector();

	Vector operator+(const Vector & other) const { return Vector(fX + other.fX, fY + other.fY); }
	Vector operator-() const { return Vector(-fX, -fY); }
	Vector operator-(const Vector & other) const { return *this + (-other); }

	Vector operator*(double mult) const { return Vector(fX * mult, fY * mult); }
	Vector operator/(double div) const { return Vector(fX / div, fY / div); }
	friend Vector operator*(double lhs, const Vector & rhs);
	
	bool operator==(const Vector & other) const;
	Vector & operator=(const Vector & other);
	
	double Dot(const Vector & other) const;
	double Arg() const;
	double Mod() const;
	Vector Norm() const;

	// Member variables are public, as access restrictions are not necessary.
	double fX;
	double fY;
};

#endif
