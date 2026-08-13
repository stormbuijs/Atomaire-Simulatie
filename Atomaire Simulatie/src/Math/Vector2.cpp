#include "Math/Vector2.h"
#include "Math/Real.h"

#include <cmath>


Vector2::Vector2(): x(0.0), y(0.0)
{
}

Vector2::Vector2(Real x, Real y) : x(x), y(y)
{
}


Real Vector2::Length() const
{
	return std::sqrt(x * x + y * y);
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

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator/(Real scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}


Real Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}