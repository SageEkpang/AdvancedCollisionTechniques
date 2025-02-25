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

	// GETTER FUNCTION(s)
	inline std::vector<Particle*> GetParticle() { m_MassPoints; }


	// SETTER FUNCTION(s)


	// HELPER FUNCTION(s)
	inline void AddParticle(Particle* particle) { m_MassPoints.push_back(particle); };
	void ClearParticle();
};

#endif