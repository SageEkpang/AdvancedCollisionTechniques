  #include "Particle.h"

Particle::Particle(float mass)
{	
	m_Mass = mass;
}

Particle::Particle()
{
	m_Mass = 1.f;
}

void Particle::Construct(float mass)
{
	m_Mass = mass;
}

void Particle::Update(float deltaTime)
{
	PhysicsEntity::Update(deltaTime);
}

