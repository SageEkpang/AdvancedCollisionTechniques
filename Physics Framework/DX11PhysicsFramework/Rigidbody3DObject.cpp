#include "Rigidbody3DObject.h"

Rigidbody3DObject::Rigidbody3DObject(float mass, Rigidbody3DMovementType rigidbody3DMovementType)
{
	m_Mass = mass;
	m_RigidbodyMovementType = rigidbody3DMovementType;
	// Store the IdentityMatrix in the InertiaTensor
	//XMStoreFloat3x3(&m_InertiaTensor, XMMatrixIdentity());

	//float Value = 0.083;

	// Box
	//m_InertiaTensor._11 = Value * mass * (std::pow(HalfExtents.y, 2.0f) + std::pow(HalfExtents.z, 2.0f));
	//m_InertiaTensor._22 = Value * mass * (std::pow(HalfExtents.x, 2.0f) + std::pow(HalfExtents.z, 2.0f));
	//m_InertiaTensor._33 = Value * mass * (std::pow(HalfExtents.x, 2.0f) + std::pow(HalfExtents.y, 2.0f));

	//// Sphere
	//m_InertiaTensor._11 = (2 / 5) * mass * std::pow(radius, 2.0f);
	//m_InertiaTensor._22 = (2 / 5) * mass * std::pow(radius, 2.0f);
	//m_InertiaTensor._33 = (2 / 5) * mass * std::pow(radius, 2.0f);
}

Rigidbody3DObject::Rigidbody3DObject()
{
	m_Mass = 0.f;
}

void Rigidbody3DObject::Construct(float mass, Rigidbody3DMovementType rigidbody3DMovementType)
{
	m_Mass = mass;
	m_RigidbodyMovementType = rigidbody3DMovementType;
}

Rigidbody3DObject::~Rigidbody3DObject()
{
	
}

void Rigidbody3DObject::Update(float deltaTime)
{
	PhysicsEntity::Update(deltaTime);
	// CalculateAngularVelocity(deltaTime);
}

void Rigidbody3DObject::CalculateAngularVelocity(float deltaTime)
{

}
