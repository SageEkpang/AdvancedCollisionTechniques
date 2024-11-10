#pragma once
#ifndef RIGIDBODY_OBJECT_H
#define RIGIDBODY_OBJECT_H

#include "Structures.h"
#include "Constants.h"
#include "PhysicsObject.h"

class RigidbodyObject : public PhysicsObject
{
private:

	XMFLOAT3X3 m_InertiaTensor;
	Vector3 m_Torque = VECTOR3_ZERO;
	Vector3 m_AngularVelocity = VECTOR3_ZERO;
	Quaternion4 m_Orientation;
	float m_Damping = 0.99f;

public:

	// CLASS FUNCTION(s)
	RigidbodyObject(Transform* transform, float mass = 1.0f); // Box
	RigidbodyObject(Transform* transform, float radius, float mass); // Sphere
	~RigidbodyObject() override;


	// BASE FUNCTION(s)
	void Update(float deltaTime) override;


	// ADDITIONAL FUNCTION(s)

	/// <summary> Add a Relative Force to the point on the object </summary>
	void AddRelativeForce(Vector3 force, Vector3 point) override;

	/// <summary> Calculate the Angular Velocity of the Point </summary>
	void CalculateAngularVelocity(float DeltaTime);


	// GETTER FUNCTION(s)
	inline float GetDamping() { return m_Damping; }

	// SETTER FUNCTION(s)
	void SetDamping(float damping) { m_Damping = damping; }

};

#endif
