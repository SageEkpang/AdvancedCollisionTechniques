#pragma once
#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

class SphereCollider : public Collider
{
private:

	float m_Radius = 0.0f;

public:

	SphereCollider::SphereCollider(Transform* transform, float radius) : Collider(transform), m_Radius(radius) { }

	// Replace these when collision manifold is implemented
	virtual bool CollidesWith(Collider& other, CollisionManifold& out) override { return other.CollidesWith(*this, out); }
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) override;
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) override;

	float GetRadius() const { return m_Radius; }
	Vector3 NearestPoint(Vector3 point);
	bool PointInSphere(Vector3 point);
};

#endif;

