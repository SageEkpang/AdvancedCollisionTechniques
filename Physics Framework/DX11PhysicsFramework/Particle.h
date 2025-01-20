#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Constants.h"
#include "Structures.h"

#include "RigidbodyObject.h"

class Particle : public RigidbodyObject
{
private:

	// Position
	// Velocity
	// Acceleration
	// Damping
	// InverseMass


public:

	// CLASS FUNCTION(s)
	Particle(Transform* transform, float mass);
	~Particle();


	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw();


	// GETTER FUNCTION(s)



	// SETTER FUNCTION(s)


};

#endif