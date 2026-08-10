#pragma once

#include "Math/Real.h"


class Vector2
{
public:

	Vector2();
	Vector2(Real x, Real y);

	Vector2 operator*(Real scalar) const;
	Vector2 operator+=(const Vector2& other);

	Real x = 0.0;
	Real y = 0.0;

};