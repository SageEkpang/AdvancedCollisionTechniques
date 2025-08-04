#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Constants.h"
#include "Structures.h"

#include "OBJLoader.h"
#include "PhysicsEntity.h"
#include "Transform.h"

// NOTE: Derives from Physics Object
class Particle
{
private:

	XMFLOAT4X4* m_World;
	Geometry m_Geometry;
	Transform* m_Transform;

	// Physics Variables
	float m_Mass;
	Vector3 m_Velocity = VECTOR3_ZERO;
	Vector3 m_Acceleration = VECTOR3_ZERO;
	Vector3 m_NetForce = VECTOR3_ZERO;

	mutable float m_Gravity = GRAVITY_EARTH;

public:

	// CLASS FUNCTION(s)
	Particle(Transform* transform, float mass, ID3D11Device* device);
	~Particle();


	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device, Vector3 colour);
	void CalculateAcceleration(float deltaTime);


	// ADDITIONAL FUNCTION(s)
	void AddForce(Vector3 force) { m_NetForce += force; }
	void ApplyImpulse(Vector3 impulse) { m_Velocity += impulse; }


	// GETTER FUNCTION(s)
	Vector3 GetVelocity() { return m_Velocity; }
	Vector3 GetAcceleration() { return m_Acceleration; }

	inline float GetMass() const { return m_Mass; }
	inline float GetInverseMass() const { if (m_Mass == 0) { return 0; } return 1 / m_Mass; }

	Vector3 GetGravity() { return Vector3(0.0f, -m_Gravity, 0.0f); }

	XMFLOAT4X4* GetPureWorld() const { return m_World; }
	XMMATRIX GetWorld() const { return XMLoadFloat4x4(m_World); }

	Transform* GetTransform() const { return m_Transform; }

	// SETTER FUNCTION(s)
	virtual inline void SetVelocity(Vector3 velocity) { m_Velocity = velocity; }
	inline void SetVelocity(float x, float y, float z) { m_Velocity = Vector3(x, y, z); }

	void ClearAccumulator();

};

#endif