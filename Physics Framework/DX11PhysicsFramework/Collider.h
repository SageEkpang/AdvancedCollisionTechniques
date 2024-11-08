#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Structures.h"
#include "Constants.h"
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

	Transform3D m_Transform;
	Vector3 m_Position;
	Vector3 m_Scale;
	// TODO: Change to quaternion
	Vector3 m_Rotation;

public:

	Collider(Vector3 position, Vector3 scale, Vector3 rotation) 
	: m_Position(position), m_Scale(scale), m_Rotation(rotation) { }
	// Collider(Transform* transform)


	virtual bool CollidesWith(Collider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) = 0;
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) = 0;

	// GETTER FUNCTION(s)
	Vector3 GetPosition() const { return m_Position; }
	Vector3 GetScale() const { return m_Position; }
	Vector3 GetRotation() const { return m_Rotation; }

};

#endif

