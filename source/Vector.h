class Vector
{
public:
	Vector();
	Vector(double x, double y);
	Vector(const Vector & other);
	~Vector();

	inline double GetX() { return fX; }
	inline double GetY() { return fY; }
	inline void SetX(double x) { fX = x; }
	inline void SetY(double y) { fY = y; }

	Vector operator+(const Vector & other) { return Vector(fX + other.fX, fY + other.fY); }
	Vector operator-() { return Vector(-fX, -fY); }
	Vector operator-(const Vector & other) { return *this + (-other); }

	Vector operator*(double mult) { return Vector(fX * mult, fY * mult); }
	Vector operator/(double div) { return Vector(fX / div, fY / div); }
	friend Vector operator*(double lhs, const Vector & rhs);
	
	bool operator==(const Vector & other);
	
	double Dot(const Vector & other);
	double Arg();
	double Mod();
	Vector Norm();

private:
	double fX;
	double fY;
};

Vector operator*(double lhs, const Vector & rhs)
{
	return Vector(lhs * rhs.fX, lhs * rhs.fY);
}

bool Vector::operator==(const Vector & other)
{
	if (fX == other.fX && fY == other.fY)
		return true;
	else
		return false;
}
