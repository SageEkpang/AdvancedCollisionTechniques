#pragma once
#ifndef RIGIDBODY_OBJECT_H
#define RIGIDBODY_OBJECT_H

#include "Structures.h"
#include "Constants.h"
#include "PhysicsObject.h"
#include "MaterialCoefficient.h"

// RIGIDBODY PHYSICS

class RigidbodyObject : public PhysicsObject
{
private:

	// ROTATION TENSOR (MATRIX)
	XMFLOAT3X3 m_InertiaTensor;

	// ROTATION VARIABLE(s)
	Quaternion4 m_Orientation;

	Vector3 m_Torque = VECTOR3_ZERO;
	Vector3 m_AngularVelocity = VECTOR3_ZERO;
	float m_AngularDamping = 0.99f;

	
	// MATERIAL VARIABLE(s) 
	MaterialTypes m_MaterialType;

public:

	// CLASS FUNCTION(s)
	RigidbodyObject(Transform* transform, float mass = 1.0f); // Box
	RigidbodyObject(Transform* transform, float radius, float mass); // Sphere
	~RigidbodyObject() override;


	// BASE FUNCTION(s)
	void Update(float deltaTime) override;


	// The direction of the force is given in world coordinates
	void AddForceAddBodyPoint(const Vector3& force, const Vector3& point);

	// Not Applied to the at the center of mass, it may be split into both a force and torque
	void AddForceAtPoint(const Vector3& force, const Vector3& point);



	// ADDITIONAL FUNCTION(s)

	/// <summary> Add a Relative Force to the point on the object </summary>
	void AddRelativeForce(Vector3 force, Vector3 point) override;

	/// <summary> Calculate the Angular Velocity of the Point </summary>
	void CalculateAngularVelocity(float DeltaTime);


	// GETTER FUNCTION(s)
	inline float GetAngularDamping() { return m_AngularDamping; }
	inline MaterialTypes GetMaterial() const { return m_MaterialType; }

	// SETTER FUNCTION(s)
	void SetAngularDamping(float damping) { m_AngularDamping = damping; }
	void SetMaterial(MaterialTypes material) { m_MaterialType = material; }
};

#endif
