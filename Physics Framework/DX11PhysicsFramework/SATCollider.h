#pragma once
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

	Vector3 m_Max;
	Vector3 m_Min;
	Vector3 m_Orientation;

	Vector3 m_CentrePoint; // NOTE: Position;
	Vector3 m_U[3]; // NOTE: Tensor
	float m_Extents[3]; // NOTE: Extents 

	float m_Size[3] = { 0 };
	float m_OrientationArray[3] = { 0 };


public:


	// CLASS FUNCTION(s)
	SATCollider(Vector3 position, Vector3 scale, Vector3 rotation, float mass = 1.f);
	~SATCollider();

	// bool ObjectCollision(OBBCollider* objectA, OBBCollider* objectB, CollisionManifold& out);
	bool ObjectCollisionAlt(OBBCollider& objectA, OBBCollider& objectB, CollisionManifold& out);

	// GETTER FUNCTION(s)
	Vector3 GetPosition() { return m_CentrePoint; }
	Vector3 GetScale() { return Vector3(m_Extents[0], m_Extents[1], m_Extents[2]); }




	// SETTER FUNCTION(s)


	// HELPER FUNCTION(s)
	bool OverlapOnAxis(OBBCollider& obbA, OBBCollider& obbB, Vector3& axis);

};

#endif
