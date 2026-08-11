#include "Physics/Particle.h"


Particle::Particle()
	: position(0.0, 0.0), velocity(0.0, 0.0), mass(1.0), radius(1.0), charge(0.0)
{
}

Particle::Particle(const Vector2& position, Real mass, Real radius, Real charge)
	: position(position), velocity(0.0, 0.0), mass(mass), radius(radius), charge(charge)
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

Real Particle::GetCharge() const
{
	return charge;
}


void Particle::SetPosition(const Vector2& position)
{
	this->position = position;
}

void Particle::SetVelocity(const Vector2& velocity)
{
	this->velocity = velocity;
}

void Particle::ApplyForce(const Vector2& force)
{
	accumulatedForce += force;
}


void Particle::Integrate(Real deltaTime)
{
	Vector2 acceleration = accumulatedForce / mass;

	// Semi-implicit Euler aanpak: eerst snelheid dan positie
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;


	accumulatedForce = Vector2(0.0, 0.0);
}