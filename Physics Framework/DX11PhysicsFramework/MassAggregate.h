#pragma once
#ifndef MASS_AGGREGATE_H
#define MASS_AGGERGATE_H

// ABSTRACT CLASS(s)
#include "Collider.h"
#include "Particle.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"
#include "CollisionContact.h"

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

// NOTE: THIS IS THE MASS OBJECT TO SIMULATE
class MassAggregate
{
private: // PRIVATE VARIABLE(s)

	CollisionContact* m_CollisionContact;
	std::vector<Particle*> m_MassPoints;
	std::vector<Particle*> m_StaticPoints;
	float m_Mass;
	int m_Size;

public: // PUBLIC VARIABLE(s)

	// CLASS FUNCTION(s)
	MassAggregate(char* filePath, Vector3 position, float mass, int size, ID3D11Device* device);
	~MassAggregate();


	// BASE FUNCTION(s)
	void Update(float deltaTime); // Update Function
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

	void ResolveVelocity(Particle* particleA, Particle* particleB, float duration, Vector3 collisionNormal);
	void ResolveInterpenetration(Particle* particleA, Particle* particleB, float penetration, float duration, Vector3 collisionNormal);

	// GETTER FUNCTION(s)
	inline std::vector<Particle*> GetParticle() { m_MassPoints; }


	// SETTER FUNCTION(s)


	// HELPER FUNCTION(s)
	inline void AddParticle(Particle* particle) { m_MassPoints.push_back(particle); };
	Vector3 CalculateSeparatingVelocity(Particle* particleA, Particle* particleB, Vector3 contactNormal);
	void MovePoints(Particle* particle, int index);
	void ClearParticle();
};

#endif