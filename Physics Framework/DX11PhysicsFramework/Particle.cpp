#include "Particle.h"

Particle::Particle(Transform* transform, float mass)
	: RigidbodyObject(transform, mass)
{





}

Particle::~Particle()
{



}

void Particle::Update(float deltaTime)
{
	RigidbodyObject::Update(deltaTime);
}

void Particle::Draw()
{


}
