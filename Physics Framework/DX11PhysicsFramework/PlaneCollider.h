#pragma once
#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

class PlaneCollider : public Collider
{
private:

	// Min and Max Corners
	Vector3 m_Max;
	Vector3 m_Min;

	// Min Extents
	Vector3 m_Extents; // Diameter dx, dy, dz
	Vector3 m_HalfExtents; // Radius rx, ry, rz

	// Centre and Half Extents
	Vector3 m_CentrePoint;
	Vector3 m_PlaneNormal;

public:

	// PlaneCollider(Transform* transform, Vector3 planeNormal) : Collider(transform) { m_PlaneNormal = planeNormal; }
	
	PlaneCollider(Vector3 position, Vector3 scale, Vector3 rotation)
		: Collider(position, scale, rotation) { }

	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) override;

	inline Vector3 GetMax() { return m_Max; }
	inline Vector3 GetMin() { return m_Min; }
	inline Vector3 GetExtents() { return m_Extents; }
	inline Vector3 GetHalfExtents() { return m_Extents / 2; }
	inline Vector3 GetCentrePoint() { return m_CentrePoint; }
	inline Vector3 GetPlaneNormal() { return m_PlaneNormal; }
	Vector3 NearestPoint(Vector3 point);
};

#endif;

