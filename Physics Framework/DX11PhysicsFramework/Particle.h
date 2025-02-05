#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Constants.h"
#include "Structures.h"

#include "PhysicsObject.h"

// NOTE: Derives from Physics Object
class Particle : public PhysicsObject
{
private:


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