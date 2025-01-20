#pragma once
#ifndef MASS_POINT_SPRING
#define MASS_POINT_SPRING

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"


// TODO: Make Particle Class
#include "Particle.h"

class MassPointSpring
{
private:

	Particle* m_Other;
	double m_SpringConstant;
	double m_RestLength;

public:

	MassPointSpring(Particle* other, double springConstant, double restLength);
	~MassPointSpring();

	virtual void UpdateForce(Particle* particle, float deltaTime);





};

#endif