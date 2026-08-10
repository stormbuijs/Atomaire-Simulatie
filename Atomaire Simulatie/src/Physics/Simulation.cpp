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


const std::vector<Particle>& Simulation::GetParticles() const
{
	return particles;
}