#pragma once

#include <vector>

#include "Physics/Particle.h"
#include "Math/Real.h"


class Simulation
{
public:

	Simulation(Real width, Real height);

	void AddParticle(const Particle& particle);
	
	void Step(Real deltaTime);

	void SetTimeScale(Real scale);

	const std::vector<Particle>& GetParticles() const;

private:

	void ResolveBoundaryCollisions(Particle& particle) const;


	std::vector<Particle> particles;

	Real width;
	Real height;

	Real timeScale = 1.0;


	Vector2 CalculateCoulombForce(const Particle& a, const Particle& b) const;

	Real coulombConstant = 1500000.0;

};