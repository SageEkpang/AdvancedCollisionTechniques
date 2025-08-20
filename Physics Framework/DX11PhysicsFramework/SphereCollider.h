#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

class SphereCollider : public ColliderEntity
{
public:

	float m_Radius = 0.0f;
	Vector3 m_Offset;

public:

	// CLASS FUNCTION(s) (General)
	SphereCollider(Vector3 offset, float radius);
	SphereCollider(float x_offset, float y_offset, float z_offset, float radius);
	SphereCollider(float radius);

	// CLASS FUNCTION(s) (Components)
	SphereCollider();

	void Construct(Vector3 offset, float radius);
	void Construct(float x_offset, float y_offset, float z_offset, float radius);
	void Construct(float radius);


	// GETTER FUNCTIONS
	Vector3 NearestPoint(Vector3 point);
	bool PointInSphere(Vector3 point);
};

#endif;

