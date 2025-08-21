#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

class BoxCollider : public ColliderEntity
{
public:

	Vector3 m_Offset;
	Vector3 m_Scale;

public:

	// CLASS FUNCTION(s) (General)
	BoxCollider(Vector3 offset, Vector3 scale);
	BoxCollider(Vector3 offset, float width, float height, float length);
	BoxCollider(Vector3 scale);
	BoxCollider(float x_offset, float y_offset, float z_offset, float width, float height, float length);

	// CLASS FUNCTION(s) (Components)
	BoxCollider();

	void Construct(Vector3 offset, Vector3 scale);
	void Construct(Vector3 offset, float width, float height, float length);
	void Construct(Vector3 scale);
	void Construct(float x_offset, float y_offset, float z_offset, float width, float height, float length);

	// GETTER FUNCTION(s)
	inline Vector3 GetMax();
	inline Vector3 GetMin();
	inline const Vector3 GetExtents() { return m_Scale; }
	inline Vector3 GetHalfExtents() { return m_Scale / 2; }
};

#endif
