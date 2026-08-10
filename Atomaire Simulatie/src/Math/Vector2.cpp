#include "Math/Vector2.h"
#include "Math/Real.h"


Vector2::Vector2(): x(0.0), y(0.0)
{
}

Vector2::Vector2(Real x, Real y) : x(x), y(y)
{
}

Vector2 Vector2::operator*(Real scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}