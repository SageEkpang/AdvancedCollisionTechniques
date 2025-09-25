#ifndef PARTICLE_H
#define PARTICLE_H

#include "OBJLoader.h"
#include "Constants.h"

#include "ConstantBuffer.h"
#include "Geometry.h"
#include "Material.h"
#include "Vector3.h"
#include <directxmath.h>

using namespace DirectX;

// NOTE: Derives from Physics Object
class Particle
{
public:

	Vector3 m_Position;
	XMFLOAT4X4* m_World;
	Geometry m_Geometry;

	// Physics Variables
	float m_Mass;
	Vector3 m_Velocity = VECTOR3_ZERO;
	Vector3 m_Acceleration = VECTOR3_ZERO;
	Vector3 m_NetForce = VECTOR3_ZERO;

	mutable float m_Gravity = 9.81f;

public:

	// CLASS FUNCTION(s)
	Particle(Vector3 position, float mass, ID3D11Device* device);
	~Particle();

	/// <summary> Add Gravity force that effects the objects downwards force </summary>
	Vector3 GravityForce();

	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device, Vector3 colour);
	
	void CalculateAcceleration(float deltaTime);


	// ADDITIONAL FUNCTION(s)
	void AddForce(Vector3 force) { m_NetForce += force; }
	void ApplyImpulse(Vector3 impulse) { m_Velocity += impulse; }

	// GETTER FUNCTION(s)
	inline float GetMass() const { return m_Mass; }
	inline float GetInverseMass() const { if (m_Mass == 0) { return 0; } return 1 / m_Mass; }


	// SETTER FUNCTION(s)
	void ClearAccumulator();
	void SetPosition(Vector3 position) { m_Position = position; }

};

#endif