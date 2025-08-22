#ifndef RIGIDBODY_OBJECT_H
#define RIGIDBODY_OBJECT_H

#include "PhysicsEntity.h"
#include "MaterialCoefficient.h"

// RIGIDBODY PHYSICS
enum Rigidbody3DMovementType
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

	Vector3 m_Torque = VECTOR3_ZERO;
	Vector3 m_AngularVelocity = VECTOR3_ZERO;
	Rigidbody3DMovementType m_RigidbodyMovementType;

	// MATERIAL VARIABLE(s) 
	MaterialTypes m_MaterialType;

public:

	// CLASS FUNCTION(s) (General)
	Rigidbody3DObject(float mass, Rigidbody3DMovementType rigidbody3DMovementType);


	// CLASS FUNCTION(s) (Components)
	Rigidbody3DObject();
	~Rigidbody3DObject() override;

	void Construct(float mass, Rigidbody3DMovementType rigidbody3DMovementType);


	// BASE FUNCTION(s)
	void Update(float deltaTime) override;

	// ADDITIONAL FUNCTION(s)
	void CalculateAngularVelocity(float deltaTime);

};

#endif
