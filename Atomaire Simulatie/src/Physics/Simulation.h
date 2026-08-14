#pragma once

#include <vector>

#include "Physics/Particle.h"
#include "Math/Real.h"
#include "Physics/Element.h"
#include "Physics/SimulationConfiguration.h"


class Simulation
{
public:

	Simulation(Real width, Real height, const SimulationConfiguration& configuration = SimulationConfiguration());


	struct Bond
	{
		size_t particleIndexA;
		size_t particleIndexB;
		Real restLength;
	};

	struct Atom
	{
		ElementType type = ElementType::Hydrogen;
		size_t nucleusIndex = 0;
		std::vector<size_t> lonePairIndices;
	};


	size_t AddParticle(const Particle& particle);

	Atom CreateAtom(ElementType type, const Vector2& position);

	
	void Step(Real deltaTime);
	void SetTimeScale(Real scale);

	void AddBond(size_t indexA, size_t indexB, Real restLength);
	void BondAtoms(Atom& a, Atom& b);

	void PreSolveBondConstraints();

	const std::vector<Particle>& GetParticles() const;

private:

	void ResolveBoundaryCollisions(Particle& particle) const;

	
	std::vector<Particle> particles;

	Real width;
	Real height;

	Real timeScale = 1;


	SimulationConfiguration configuration;


	Vector2 CalculateCoulombForce(const Particle& a, const Particle& b) const;

	Vector2 CalculatePauliRepulsionForce(const Particle& a, const Particle& b) const;


	void ApplyBondContraints(const int iterations);

	void SatisfyBondConstraints(Real deltaTime, const std::vector<Vector2>& positionsBeforeStep);

	std::vector<Bond> bonds;

};