#include "Physics/Simulation.h"


Simulation::Simulation(Real width, Real height) : width(width), height(height)
{
}


void Simulation::AddParticle(const Particle& particle)
{
	particles.push_back(particle);
}

void Simulation::Step(Real deltaTime)
{
	Real scaledDeltaTime = deltaTime * timeScale;


	// Voor elk paar deeltjes, verdeel de Coulomb-kracht
	for (size_t i = 0; i < particles.size(); ++i)
	{
		for (size_t j = i + 1; j < particles.size(); ++j)
		{
			Vector2 force = CalculateCoulombForce(particles[i], particles[j]);

			// Newtons derde wet: actie = -reactie
			particles[i].ApplyForce(force);
			particles[j].ApplyForce(force * -1.0);
		}
	}

	
	for (Particle& particle : particles)
	{
		particle.Integrate(scaledDeltaTime);
		ResolveBoundaryCollisions(particle);
	}


	// TODO: particle-particle botsingen
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


Vector2 Simulation::CalculateCoulombForce(const Particle& a, const Particle& b) const
{
	Vector2 direction = b.GetPosition() - a.GetPosition();
	Real actualDistance = direction.Length();


	// Voorkom deling door nul als deeltjes precies overlappen
	if (actualDistance < 0.0001)
	{
		return Vector2(0.0, 0.0);
	}


	Vector2 unitDirection = direction / actualDistance;


	// Voorkom oneindig grote krachten wanneer deeltjes overlappen
	// Gebruik nooit een kleinere afstand dan de som van hun radii
	Real minimumDistance = a.GetRadius() + b.GetRadius();
	Real distance = (actualDistance < minimumDistance) ? minimumDistance : actualDistance;


	Real forceMagnitude = coulombConstant * a.GetCharge() * b.GetCharge() / (distance * distance);


	// Gelijke ladingen duwen weg van elkaar, dus de kracht op 'a' wijst dan tegen de unitDirection in
	return unitDirection * -forceMagnitude;
}


const std::vector<Particle>& Simulation::GetParticles() const
{
	return particles;
}