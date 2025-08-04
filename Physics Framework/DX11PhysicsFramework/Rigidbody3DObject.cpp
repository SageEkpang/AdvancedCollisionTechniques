#include "Rigidbody3DObject.h"

Rigidbody3DObject::Rigidbody3DObject(Transform* transform, float mass)
	: PhysicsEntity(transform, mass)
{
	// Store the IdentityMatrix in the InertiaTensor
	XMStoreFloat3x3(&m_InertiaTensor, XMMatrixIdentity());

	Vector3 HalfExtents = transform->m_Scale / 2;

	float Value = 0.083;

	m_Mass = mass;

	// Box
	m_InertiaTensor._11 = Value * mass * (std::pow(HalfExtents.y, 2.0f) + std::pow(HalfExtents.z, 2.0f));
	m_InertiaTensor._22 = Value * mass * (std::pow(HalfExtents.x, 2.0f) + std::pow(HalfExtents.z, 2.0f));
	m_InertiaTensor._33 = Value * mass * (std::pow(HalfExtents.x, 2.0f) + std::pow(HalfExtents.y, 2.0f));
}

Rigidbody3DObject::Rigidbody3DObject(Transform* transform, float radius, float mass)
	: PhysicsEntity(transform, mass)
{
	// Store the IdentityMatrix in the InertiaTensor
	XMStoreFloat3x3(&m_InertiaTensor, XMMatrixIdentity());

	m_Mass = mass;

	// Sphere
	m_InertiaTensor._11 = (2 / 5) * mass * std::pow(radius, 2.0f);
	m_InertiaTensor._22 = (2 / 5) * mass * std::pow(radius, 2.0f);
	m_InertiaTensor._33 = (2 / 5) * mass * std::pow(radius, 2.0f);

	// NOTE: The inertia tensor for the mass aregate system would not be to be used due to spring forces and constants
}

Rigidbody3DObject::~Rigidbody3DObject()
{
	delete m_Transform;
}

void Rigidbody3DObject::Update(float deltaTime)
{
	// CalculateAngularVelocity(deltaTime);
	PhysicsEntity::Update(deltaTime);
}

void Rigidbody3DObject::AddForceAddBodyPoint(const Vector3& force, const Vector3& point)
{
	// Convert to coordinates relative to center of mass.
	// Vector3 t_Point;


}

//void RigidbodyObject::AddForceAtPoint(const Vector3& force, const Vector3& point)
//{
//	Vector3 t_Point = point;
//	t_Point -= m_Transform->GetPosition();
//
//	m_NetForce += force;
//	// m_Torque += t_Point % force;
//
//}
//
//void RigidbodyObject::AddRelativeForce(Vector3 force, Vector3 point)
//{
//	// AddForce(force); // Force
//	m_Torque = Vector::CalculateCrossProductV(point, force); // Force Vector
//}
//
//void RigidbodyObject::CalculateAngularVelocity(float DeltaTime)
//{
//	// Calculate if Mass is not 0
//	if (m_Mass == 0) { return; }
//
//	if (Vector::Magnitude(m_Torque) > 0)
//	{
//		// Create Temp Variables for Storation
//		XMMATRIX TempMatrix = XMLoadFloat3x3(&m_InertiaTensor);
//		XMVECTOR TempTor = XMVectorSet(m_Torque.x, m_Torque.y, m_Torque.z, 0.0f);
//
//		// Inverse and Transform Inertia Tensor to Calculate Acceleration
//		XMMatrixInverse(nullptr, TempMatrix); // Inverse Inertia Tensor
//		XMVector3Transform(TempTor, TempMatrix); // Angular Accelertation
//
//		// Convert to Vector3
//		XMFLOAT3 Convert = XMFLOAT3();
//		XMStoreFloat3(&Convert, TempTor);
//
//		Vector3 AngularAcceleration = Vector::XMFLOAT3toVector3(Convert);
//
//		// Calculating Angular Velocity
//		m_AngularVelocity += AngularAcceleration * DeltaTime;
//	}
//
//	// Set Orientation
//	Quaternion4 Orient = m_Transform->GetOrientation();
//	Orient += (Orient * m_AngularVelocity) * 0.5 * DeltaTime;
//
//	// Calculate the Orientation and augmenting the transform
//	if (Orient.Magnitude() != 0) { m_Transform->SetOrientation(Orient / Orient.Magnitude()); }
//
//	// Dampen the Angular Velocity
//	m_AngularVelocity *= std::pow(m_AngularDamping, DeltaTime);
//	m_Torque = Vector3();
//}
