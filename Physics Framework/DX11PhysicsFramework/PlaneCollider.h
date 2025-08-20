#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

class PlaneCollider : public ColliderEntity
{
private:

	Vector3 m_Offset;
	Vector3 m_Scale;

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

	// CLASS FUNCTION(s) (General)
	PlaneCollider(Vector3 offset, Vector3 scale);
	PlaneCollider(Vector3 offset, float width, float height, float length);
	PlaneCollider(Vector3 scale);
	PlaneCollider(float x_offset, float y_offset, float z_offset, float width, float height, float length);

	// CLASS FUNCTION(s) (Components)
	PlaneCollider();

	void Construct(Vector3 offset, Vector3 scale);
	void Construct(Vector3 offset, float width, float height, float length);
	void Construct(Vector3 scale);
	void Construct(float x_offset, float y_offset, float z_offset, float width, float height, float length);


	// GETTER FUNCTION(s)
	inline Vector3 GetMax() { return m_Max; }
	inline Vector3 GetMin() { return m_Min; }
	inline Vector3 GetExtents() { return m_Extents; }
	inline Vector3 GetHalfExtents() { return m_Extents / 2; }
	inline Vector3 GetPlaneNormal() { return m_PlaneNormal; }

	Vector3 NearestPoint(Vector3 point);
	bool PointOnPlane(Vector3 point);
};

#endif;

