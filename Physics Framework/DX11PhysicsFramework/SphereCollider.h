#pragma once
#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

class SphereCollider : public ColliderEntity
{
private:

	float m_Radius = 0.0f;

public:

	//SphereCollider(Transform* transform, float radius) { }

	// Replace these when collision manifold is implemented

	float GetRadius() const { return m_Radius; }
	Vector3 NearestPoint(Vector3 point);
	bool PointInSphere(Vector3 point);
};

#endif;

