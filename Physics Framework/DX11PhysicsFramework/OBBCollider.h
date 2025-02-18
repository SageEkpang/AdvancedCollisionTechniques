#ifndef OBB_COLLIDER_H
#define OBB_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Structures.h"
#include "Constants.h"

class OBBCollider : public Collider
{
private:

	Vector3 m_Max;
	Vector3 m_Min;
	Vector3 m_Orientation;

	Vector3 m_CenterPoint; // Position
	Vector3 m_U[3]; // Tensor // NOTE: Local X, Y, Z AXES
	float m_Extents[3]; // Extents

	float m_Size[3] = { 0 }; // TODO: Fill this with values // TODORE: Depricated, remove these when possible
	float m_OrientationArray[9] = { 0 }; // Make a function for this instead // TODORE: Depricated, remove these when possible

public:

	// CLASS FUNCTION(s)
	OBBCollider(Transform* transform, Vector3 rotation) : Collider(transform) 
	{ 
		// NOTE: Extents of the Bound Box to be tested
		m_Extents[0] = transform->GetScale().x;
		m_Extents[1] = transform->GetScale().y;
		m_Extents[2] = transform->GetScale().z;

		// NOTE: Rotation Matrix
		m_U[0] = Vector3(rotation.x, 0, 0);
		m_U[1] = Vector3(0, rotation.y, 0);
		m_U[2] = Vector3(0, 0, rotation.z);

		m_OrientationArray[0] = rotation.x;
		m_OrientationArray[1] = 0;
		m_OrientationArray[2] = 0;

		m_OrientationArray[3] = 0;
		m_OrientationArray[4] = rotation.y;
		m_OrientationArray[5] = 0;

		m_OrientationArray[6] = 0;
		m_OrientationArray[7] = 0;
		m_OrientationArray[8] = rotation.z;

	}

	// BASE FUNCTION(s)
	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) override;

	virtual bool CollidesWith(SATCollider& other, CollisionManifold& out) override; // TODO: Add to other classes


	// GETTER FUNCTION(s)
	Vector3 GetOrientation() { return m_Orientation; }
	const float* GetOrientationArray() { return m_OrientationArray; }

	Vector3* GetUArray() { return m_U; }


	// HELPER FUNCTION(s)
	Vector3 NearestPoint(Vector3 point);
	bool PointInOBB(Vector3 point);
};

#endif