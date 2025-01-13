#pragma once
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

	float m_Size[3]; // TODO: Fill this with values
	float m_OrientationArray[9]; // Make a function for this instead

public:

	// CLASS FUNCTION(s)
	OBBCollider(Transform* transform) : Collider(transform) { }

	// BASE FUNCTION(s)
	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) override;

	// GETTER FUNCTION(s)
	Vector3 GetOrientation() { return m_Orientation; }
	const float* GetOrientationArray() { return m_OrientationArray; }

	// HELPER FUNCTION(s)
	Vector3 NearestPoint(Vector3 point);
	bool PointInOBB(Vector3 point);
};

#endif