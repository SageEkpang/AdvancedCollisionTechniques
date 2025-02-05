#pragma once
#ifndef MASS_AGGREGATE_H
#define MASS_AGGERGATE_H

// ABSTRACT CLASS(s)
#include "Collider.h"
#include "Particle.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// MASS AGGREGATE
/*
	DESCRIPTION:
	Describes the use of different points to create a mass body system that simulates physics on
	each point with constraints to other points as part of the geometry

	PROBLEMS:
	The problem with this is the modelling of the shape that the mass system will be using for the Mass
	aggregation. Simple shapes such as Boxes and Diamonds can be made, but smoother shapes, such as cirles
	can be long to make and simulating physics on each point can be hard to do as well.
	
	SOLUTION:
	Either only use simple polyhedrons or use a convex hull generating algorithm for creating and storing only some of the
	points that make up the object. This means instead of simulating on all the points, we only simulate the mass on the points
	that are generating by the convex hull generating algorithm.
*/

typedef struct MassPoint
{
	Vector3 position;
	int mass;
};

// NOTE: THIS IS THE MASS OBJECT TO SIMULATE
class MassAggregate
{
private: // PRIVATE VARIABLE(s)

	Transform* m_Transform;
	std::vector<Particle*> m_MassPoints;
	std::vector<Vector3> m_PositionPoints;

private: // PRIVATE FUNCTION(s)

	void FillVeritcesArray();

public: // PUBLIC VARIABLE(s)

	// CLASS FUNCTION(s)
	MassAggregate(const char* filePath);
	~MassAggregate();


	// BASE FUNCTION(s)
	void SimulatePhysicsPoints(float deltaTime); // Update Function


	// GETTER FUNCTION(s)
	inline std::vector<Particle*> GetParticle() { m_MassPoints; }


	// SETTER FUNCTION(s)
	inline void AddParticle(Particle* particle) { m_MassPoints.push_back(particle) };
	void ClearParticle();

};

#endif