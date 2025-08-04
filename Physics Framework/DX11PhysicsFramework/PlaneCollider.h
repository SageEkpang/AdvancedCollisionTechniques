#pragma once
#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

class PlaneCollider : public ColliderEntity
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

	// PlaneCollider(Transform* transform) { }

	inline Vector3 GetMax() { return m_Max; }
	inline Vector3 GetMin() { return m_Min; }
	inline Vector3 GetExtents() { return m_Extents; }
	inline Vector3 GetHalfExtents() { return m_Extents / 2; }
	inline Vector3 GetCentrePoint() { return m_CentrePoint; }
	inline Vector3 GetPlaneNormal() { return m_PlaneNormal; }

	Vector3 NearestPoint(Vector3 point);
	bool PointOnPlane(Vector3 point);
};

#endif;

