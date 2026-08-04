#pragma once

#include "Math/Vector2.h"
#include "Math/Real.h"


class Particle
{
public:

	Particle();

	Particle(
		const Vector2& position,
		Real mass,
		Real radius
	);

	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;

	Real GetMass() const;
	Real GetRadius() const;

	void SetVelocity(const Vector2& velocity);

private:

	Vector2 position;
	Vector2 velocity;

	Real mass;
	Real radius;

};