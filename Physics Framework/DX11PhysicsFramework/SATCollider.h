#ifndef SAT_COLLIDER_H
#define SAT_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"
#include "OBBCollider.h"

class SATCollider
{
private:

	Transform* m_Transform;
	Vector3 m_Rotation; // NOTE: Euler Rotation for SAT
	Geometry m_Geometry;

	Vector3 m_Max;
	Vector3 m_Min;

	// NOTE: Physics Variable(s)
	float m_Mass;
	Vector3 m_Velocity = VECTOR3_ZERO;
	Vector3 m_Acceleration = VECTOR3_ZERO;
	Vector3 m_NetForce = VECTOR3_ZERO;
	mutable float m_Gravity = GRAVITY_EARTH;

public:

	// CLASS FUNCTION(s)
	SATCollider(char* fileName, Transform* transform, Vector3 rotation, float mass, ID3D11Device* device);
	~SATCollider();


	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);
	void CalculateAcceleration(float deltaTime);
	void ClearAccumulator();

	void ResolveVelocity(SATCollider* satA, SATCollider* satB, float duration, Vector3 collisionNormal);
	void ResolveInterpenetration(SATCollider* satA, SATCollider* satB, float penetration, float duration, Vector3 collisionNormal);

	static bool ObjectCollisionAlt(SATCollider objectA, SATCollider objectB, CollisionManifold& out);


	// GETTER FUNCTION(s)
	Vector3 GetPosition() { return m_Transform->GetPosition(); }
	Vector3 GetScale() { return m_Transform->GetScale(); }
	Vector3 GetRotation() { return m_Rotation; }

	// HELPER FUNCTION(s)
	static bool OverlapOnAxis(SATCollider& satA, SATCollider& satB, Vector3& axis);
	static Interval GetIntervalOr(SATCollider& sat, Vector3& axis);
};

#endif
