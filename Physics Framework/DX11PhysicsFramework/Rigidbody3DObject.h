#ifndef RIGIDBODY_OBJECT_H
#define RIGIDBODY_OBJECT_H

#include "PhysicsEntity.h"
#include "MaterialCoefficient.h"

// RIGIDBODY PHYSICS

enum class Rigidbody3DMovementType : std::int8_t
{
	RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC,
	RIGIDBODY_3D_MOVEMENT_TYPE_STATIC,
	RIGIDBODY_3D_MOVEMENT_TYPE_KINEMATIC
};


class Rigidbody3DObject : public PhysicsEntity
{
public:

	// ROTATION TENSOR (MATRIX)
	XMFLOAT3X3 m_InertiaTensor;

	// ROTATION VARIABLE(s)
	Quaternion4 m_Orientation;

	Vector3 m_Torque = VECTOR3_ZERO;
	Vector3 m_AngularVelocity = VECTOR3_ZERO;
	float m_AngularDamping = 0.99f;
	Rigidbody3DMovementType m_RigidbodyMovementType;

	
	// MATERIAL VARIABLE(s) 
	MaterialTypes m_MaterialType;

public:

	// CLASS FUNCTION(s)
	Rigidbody3DObject(Transform* transform, float mass = 1.0f); // Box
	Rigidbody3DObject(Transform* transform, float radius, float mass); // Sphere
	~Rigidbody3DObject() override;


	// BASE FUNCTION(s)
	void Update(float deltaTime) override;


	// The direction of the force is given in world coordinates
	void AddForceAddBodyPoint(const Vector3& force, const Vector3& point);

	// Not Applied to the at the center of mass, it may be split into both a force and torque
	void AddForceAtPoint(const Vector3& force, const Vector3& point) { }


	void ApplyImpulseX(float x_force) { }
	void ApplyImpulseY(float y_force) { }
	void ApplyImpulseZ(float z_force) { }



	// ADDITIONAL FUNCTION(s)

	/// <summary> Add a Relative Force to the point on the object </summary>
	void AddRelativeForce(Vector3 force, Vector3 point) { };

	/// <summary> Calculate the Angular Velocity of the Point </summary>
	void CalculateAngularVelocity(float DeltaTime) { };


	// GETTER FUNCTION(s)
	inline float GetAngularDamping() { return m_AngularDamping; }
	inline MaterialTypes GetMaterial() const { return m_MaterialType; }

	// SETTER FUNCTION(s)
	void SetAngularDamping(float damping) { m_AngularDamping = damping; }
	void SetMaterial(MaterialTypes material) { m_MaterialType = material; }
};

#endif
