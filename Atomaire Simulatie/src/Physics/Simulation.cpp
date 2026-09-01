#include "Physics/Simulation.h"

#include <cmath>


Simulation::Simulation(Real width, Real height, const SimulationConfiguration& configuration)
	: width(width), height(height), configuration(configuration)
{
}


size_t Simulation::AddParticle(const Particle& particle)
{
	// Voeg een nieuw deeltje toe aan de simulatie en geef de index
	particles.push_back(particle);
	return particles.size() - 1;
}


Simulation::Atom Simulation::CreateAtom(ElementType type, const Vector2& position)
{
	ElementData data = GetElementData(type);

	Real nucleusCharge = GetValenceElectronCount(data);

	Atom atom;
	atom.type = type;
	atom.nucleusIndex = AddParticle(
		Particle(position, data.mass, configuration.nucleusRadius, nucleusCharge)
	);

	// Voeg voor elk vrij elektronenpaar een deeltje toe
	// Elk elektronenpaar heeft een lading van -2
	for (int iteration = 0; iteration < data.lonePairCount; ++iteration)
	{
		Real angle = static_cast<Real>(iteration) * 1.3;
		Vector2 offset(std::cos(angle) * 8.0, std::sin(angle) * 8.0);

		size_t pairIndex = AddParticle(
			Particle(
				position + offset,
				configuration.electronPairMass,
				configuration.electronPairRadius,
				configuration.electronPairCharge
			)
		);

		AddBond(atom.nucleusIndex, pairIndex, configuration.bondLength);

		atom.lonePairIndices.push_back(pairIndex);
	}

	return atom;
}


void Simulation::Step(Real deltaTime)
{
	Real scaledDeltaTime = deltaTime * timeScale;

	// Verdeel een grote Δt in kleinere simulatiestappen
	const int substepCount = configuration.substepCount;
	Real substepDeltaTime = scaledDeltaTime / static_cast<Real>(substepCount);
	Real halfSubstepDeltaTime = substepDeltaTime * 0.5;

	for (int step = 0; step < substepCount; ++step)
	{
		// De eerste halve kick met a(t), dan drift
		ApplyPairwiseForces();


		// Onthoud de huidge positie van de deeltjes
		std::vector<Vector2> positionsBeforeStep;
		positionsBeforeStep.reserve(particles.size());

		for (Particle& particle : particles)
		{
			positionsBeforeStep.push_back(particle.GetPosition());

			particle.KickVelocity(halfSubstepDeltaTime);
			particle.DriftPosition(substepDeltaTime);
			
			ResolveBoundaryCollisions(particle);

			particle.ClearForce();
		}


		// Bindingen corrigeren op de nieuwe, gedreven positie
		ApplyBondContraints(configuration.constraintIterations);


		// Effectieve snelheid afleiden uit de werkelijke verplaatsing
		// Vangt drift en PBD-correctie in één keer op
		for (size_t index = 0; index < particles.size(); ++index)
		{
			Vector2 actualDisplacement = particles[index].GetPosition() - positionsBeforeStep[index];
			particles[index].SetVelocity(actualDisplacement / substepDeltaTime);
		}


		// Tweede halve kick met a(t+Δt), berekend op de gecorrigeerde positie
		ApplyPairwiseForces();

		for (Particle& particle : particles)
		{
			particle.KickVelocity(halfSubstepDeltaTime);
			particle.ClearForce();
		}
	}
}

void Simulation::ApplyPairwiseForces()
{
	for (size_t indexA = 0; indexA < particles.size(); ++indexA)
	{
		for (size_t indexB = indexA + 1; indexB < particles.size(); ++indexB)
		{
			Vector2 coulombForce = CalculateCoulombForce(particles[indexA], particles[indexB]);
			particles[indexA].ApplyForce(coulombForce);
			particles[indexB].ApplyForce(coulombForce * -1.0);

			Vector2 repulsionForce = CalculatePauliRepulsionForce(particles[indexA], particles[indexB]);
			particles[indexA].ApplyForce(repulsionForce);
			particles[indexB].ApplyForce(repulsionForce * -1.0);
		}
	}
}

void Simulation::AddBond(size_t indexA, size_t indexB, Real restLength)
{
	bonds.push_back({ indexA, indexB, restLength });
}

void Simulation::BondAtoms(Atom& a, Atom& b)
{
	// Alle atomen zijn met elkaar verbonden door elektronenparen
	Vector2 midpoint = (particles[a.nucleusIndex].GetPosition() + particles[b.nucleusIndex].GetPosition()) / 2.0;

	size_t bondingPairIndex = AddParticle(
		Particle(
			midpoint,
			configuration.electronPairMass,
			configuration.electronPairRadius,
			configuration.electronPairCharge
		)
	);

	AddBond(a.nucleusIndex, bondingPairIndex, configuration.bondLength);
	AddBond(b.nucleusIndex, bondingPairIndex, configuration.bondLength);
}

void Simulation::SetTimeScale(Real scale)
{
	timeScale = scale;
}

void Simulation::ResolveBoundaryCollisions(Particle& particle) const
{
	Vector2 position = particle.GetPosition();
	Vector2 velocity = particle.GetVelocity();
	Real radius = particle.GetRadius();

	// Links en rechts
	if (position.x - radius < 0.0)
	{
		position.x = radius;
		velocity.x = -velocity.x;
	}
	else if (position.x + radius > width)
	{
		position.x = width - radius;
		velocity.x = -velocity.x;
	}

	// Boven en onder
	if (position.y - radius < 0.0)
	{
		position.y = radius;
		velocity.y = -velocity.y;
	}
	else if (position.y + radius > height)
	{
		position.y = height - radius;
		velocity.y = -velocity.y;
	}

	particle.SetPosition(position);
	particle.SetVelocity(velocity);
}

void Simulation::ApplyBondContraints(const int iterations)
{
	// Maak gebruik van Position-Based Dynamics (stijve verbindingen) om oscilatie te voorkomen
	for (int interation = 0; interation < iterations; ++interation)
	{
		for (const Bond& bond : bonds)
		{
			Particle& a = particles[bond.particleIndexA];
			Particle& b = particles[bond.particleIndexB];

			Vector2 delta = b.GetPosition() - a.GetPosition();
			Real distance = delta.Length();

			if (distance < configuration.minimumDistance)
			{
				continue;
			}

			Real difference = (distance - bond.restLength) / distance;


			// Verdeel de correctie naar verhouding van massa
			// Lichte deeltjes bewegen meer dan zware deeltjes
			Real totalInverseMass = 1.0 / a.GetMass() + 1.0 / b.GetMass();
			Real weightA = (1.0 / a.GetMass()) / totalInverseMass;
			Real weightB = (1.0 / b.GetMass()) / totalInverseMass;

			Vector2 correction = delta * difference;

			a.SetPosition(a.GetPosition() + correction * weightA);
			b.SetPosition(b.GetPosition() - correction * weightB);
		}
	}
}

void Simulation::PreSolveBondConstraints()
{
	ApplyBondContraints(configuration.constraintIterations * 8);

	// Bewuest geen snelheid afleiden hier
	// Dit is een eenmalige start en geen simulatiestap
}


Vector2 Simulation::CalculateCoulombForce(const Particle& a, const Particle& b) const
{
	Vector2 direction = b.GetPosition() - a.GetPosition();
	Real actualDistance = direction.Length();


	// Voorkom deling door nul als deeltjes precies overlappen
	if (actualDistance < configuration.minimumDistance)
	{
		return Vector2(0.0, 0.0);
	}


	Vector2 unitDirection = direction / actualDistance;


	// Voorkom extreem grote krachten bij zeer kleine afstanden
	Real softening = configuration.coulombSoftening;

	Real distanceSquared = actualDistance * actualDistance + softening * softening;

	Real forceMagnitude = configuration.coulombConstant * a.GetCharge() * b.GetCharge() / distanceSquared;


	// Gelijke ladingen duwen weg van elkaar, dus de kracht op 'a' wijst dan tegen de unitDirection in
	return unitDirection * -forceMagnitude;
}

Vector2 Simulation::CalculatePauliRepulsionForce(const Particle& a, const Particle& b) const
{
	Vector2 direction = b.GetPosition() - a.GetPosition();
	Real distance = direction.Length();


	if (distance < configuration.minimumDistance)
	{
		return Vector2(0.0, 0.0);
	}


	Vector2 unitDirection = direction / distance;

	// Ongeacht de lading altijd afstonend: benadering van de Pauli-afstoting tussen elektronenwolken
	Real ratio = configuration.pauliRepulsionRadius / distance;
	Real repulsionMagnitude = configuration.pauliRepulsionStrength * std::pow(ratio, 12.0);

	return unitDirection * -repulsionMagnitude;
}


const std::vector<Particle>& Simulation::GetParticles() const
{
	return particles;
}