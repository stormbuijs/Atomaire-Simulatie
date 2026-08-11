#pragma once

#include "Math/Real.h"


class Vector2
{
public:

	Vector2();
	Vector2(Real x, Real y);

	Real Length() const;

	Vector2 operator*(Real scalar) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator/(Real scalar) const;

	Real x = 0.0;
	Real y = 0.0;

};