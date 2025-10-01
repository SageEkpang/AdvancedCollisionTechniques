#ifndef RAY_COLLIDER_H
#define RAY_COLLIDER_H

#include "ColliderEntity.h"

class RayCollider : public ColliderEntity
{
public:

	Vector3 m_Origin;
	Vector3 m_Direction;

public:

	// CLASS FUNCTION(s) (General)
	RayCollider(Vector3 origin, Vector3 direction);
	RayCollider(Vector3 origin, float x_d, float y_d, float z_d);

	// CLASS FUNCTION(s) (Components)
	RayCollider();
	~RayCollider() override { };

	void Construct(Vector3 origin, Vector3 direction);
	void Construct(Vector3 origin, float x_d, float y_d, float z_d);

	// BASE FUNCTION(s)
	void Update(float deltaTime) override { };

};

#endif