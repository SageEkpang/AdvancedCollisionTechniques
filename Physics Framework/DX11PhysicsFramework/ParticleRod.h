#ifndef PARTICLE_ROD_H
#define PARTICLE_ROD_H

#include "Constants.h"
#include "Structures.h"

#include "MassAggregate.h"

class ParticleRod
{
private:

	float m_Length;
	float m_CurrentLength;
	Particle* m_Particles;

	CollisionManifold m_CollisionManifold;

public:

	// TODO: Do particle contact
	CollisionManifold ParticleRodSimulation(Particle* particleA, Particle* particleB);

	// GETTER FUNCTION(s)
	float GetCurrentLength() { return m_CurrentLength; };

};

#endif