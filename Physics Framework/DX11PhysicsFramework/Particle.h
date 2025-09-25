#ifndef PARTICLE_H
#define PARTICLE_H

#include "PhysicsEntity.h"

// NOTE: Derives from Physics Object
class Particle : public PhysicsEntity
{
public:

	// CLASS FUNCTION(s) (General)
	Particle(float mass);

	// CLASS FUNCTION(s) (Component)
	Particle();
	~Particle() override { } ;

	void Construct(float mass);

	// BASE FUNCTION(s)
	void Update(float deltaTime) override;

};

#endif