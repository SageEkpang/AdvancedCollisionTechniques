#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

class BoxCollider : public ColliderEntity
{
private:

	Vector3 m_Offset;
	Vector3 m_Scale;

	// Min and Max Corners
	Vector3 m_Max;
	Vector3 m_Min;

	// Extents
	Vector3 m_Extents; // Diameter: dx, dy, dz
	Vector3 m_HalfExtents; // Radius: rx, ry, rz

	// Centre and Half Extents
	Vector3 m_CentrePoint;

public:

	// CLASS FUNCTION(s) (General)
	BoxCollider(Vector3 offset, Vector3 scale);
	BoxCollider(Vector3 offset, float width, float height, float length);
	BoxCollider(Vector3 scale);
	BoxCollider(float x, float y, float z, float width, float height, float length);

	// CLASS FUNCTION(s) (Components)
	BoxCollider();

	void Construct(Vector3 offset, Vector3 scale);
	void Construct(Vector3 offset, float width, float height, float length);
	void Construct(Vector3 scale);
	void Construct(float x, float y, float z, float width, float height, float length);


	// GETTER FUNCTION(s)
	inline Vector3 GetMax() { return m_Max; }
	inline Vector3 GetMin() { return m_Min; }
	inline Vector3 GetExtents() { return m_Extents; }
	inline Vector3 GetHalfExtents() { return m_Extents / 2; }
	Vector3 NearestPoint(Vector3 point);
	bool PointInBox(Vector3 point);

};

#endif
