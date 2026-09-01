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
		Real radius,
		Real charge = 0.0
	);

	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;

	Real GetMass() const;
	Real GetRadius() const;
	Real GetCharge() const;

	void SetPosition(const Vector2& position);
	void SetVelocity(const Vector2& velocity);
	void ApplyForce(const Vector2& force);

	void KickVelocity(Real deltaTime);
	void DriftPosition(Real deltaTime);
	void ClearForce();

private:

	Vector2 position;
	Vector2 velocity;

	Vector2 accumulatedForce;

	Real mass;
	Real radius;
	Real charge;

};