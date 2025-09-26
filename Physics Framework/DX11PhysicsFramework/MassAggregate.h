#pragma once
#ifndef MASS_AGGREGATE_H
#define MASS_AGGERGATE_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"
#include "Particle.h"

class GameObjectEntity;
class SphereCollider;
	
// NOTE: THIS IS THE MASS OBJECT TO SIMULATE
class MassAggregate : public ColliderEntity
{
public:

	std::vector<Vector3> m_Vertices;
	std::vector<GameObjectEntity*> m_MassPoints;
	float** m_TargetDistances = nullptr;

	float m_Size = 1.f;

public:

	// CLASS FUNCTION(s) (General)
	MassAggregate();
	~MassAggregate() override;

	void Construct(std::string path, ID3D11Device* device);

	//// BASE FUNCTION(s)
	void Update(float deltaTime) override; // Update Function
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

private:

	// HELPER FUNCTION(s)
	void FillVerticesArray(char* path, ID3D11Device* device);
};

#endif