#include "Particle.h"

Particle::Particle(Transform* transform, float mass)
	: PhysicsObject(transform, mass)
{

}

Particle::~Particle()
{



}

void Particle::Update(float deltaTime)
{
	PhysicsObject::CalculateAcceleration(deltaTime);
	m_NetForce = VECTOR3_ZERO;
	m_Acceleration = VECTOR3_ZERO;
}

void Particle::Draw()
{
	// TODO: DRAW THE PARTICLE POINTS WITH LINE CONNECTIONS

}
