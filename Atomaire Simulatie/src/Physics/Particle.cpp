#include "Physics/Particle.h"


Particle::Particle(): position(0.0, 0.0), velocity(0.0, 0.0), mass(1.0), radius(1.0)
{
}

Particle::Particle(const Vector2& position, Real mass, Real radius): position(position), velocity(0.0, 0.0), mass(mass), radius(radius)
{
}


const Vector2& Particle::GetPosition() const
{
	return position;
}

const Vector2& Particle::GetVelocity() const
{
	return velocity;
}


Real Particle::GetMass() const
{
	return mass;
}

Real Particle::GetRadius() const
{
	return radius;
}


void Particle::SetPosition(const Vector2& position)
{
	this->position = position;
}

void Particle::SetVelocity(const Vector2& velocity)
{
	this->velocity = velocity;
}

void Particle::Integrate(Real deltaTime)
{
	position += velocity * deltaTime;
}