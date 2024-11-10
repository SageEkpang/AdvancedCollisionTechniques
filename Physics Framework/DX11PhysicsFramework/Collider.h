#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Structures.h"
#include "Constants.h"
#include "Transform.h"
#include "Vector.h"

// FORWARD DEC(s)
class BoxCollider;
class PlaneCollider;
class SphereCollider;
class OBBCollider;
// class ConvexHullCollider / Rigidbody Collider;
// class ComplexCollider;

class Collider abstract
{
protected:

	Transform* m_Transform;

public:

	Collider(Transform* transform) { m_Transform = transform; }

	virtual bool CollidesWith(Collider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) = 0;

	// GETTER FUNCTION(s)
	Vector3 GetPosition() const { return m_Transform->GetPosition(); }
	Vector3 GetScale() const { return m_Transform->GetScale(); }
	Vector3 GetRotation() const { return m_Transform->GetRotation(); }

};

#endif

