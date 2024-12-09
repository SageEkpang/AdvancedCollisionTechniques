#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Structures.h"
#include "Constants.h"
#include "Transform.h"
#include "Vector.h"

#include "OBJLoader.h"

// FORWARD DEC(s)
class BoxCollider;
class PlaneCollider;
class SphereCollider;
class OBBCollider;

class ConvexHullCollider;
class QuickHullCollider;
class GJKCollider;
class SATCollider;
// class ConvexHullCollider / Rigidbody Collider;
// class ComplexCollider;

class Collider
{
protected:

	Transform* m_Transform;
	Material m_Material;
	Geometry m_Geometry;
	bool m_RenderCollision = true;

public:

	// CLASS FUNCTION(s)
	Collider(Transform* transform) { m_Transform = transform; }


	// BASE FUNCTION(s)
	virtual bool CollidesWith(Collider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) { return false; }
	// virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) = 0;

	void Draw(ID3D11DeviceContext* pImmediateContext);


	// GETTER FUNCTION(s)
	inline Transform* GetTransform() { return m_Transform; }

	inline Vector3 GetPosition() const { return m_Transform->GetPosition(); }
	inline Vector3 GetScale() const { return m_Transform->GetScale(); }
	inline Vector3 GetRotation() const { return m_Transform->GetRotation(); }

	inline bool GetRenderCollision() const { return m_RenderCollision; }

	// SETTER FUNCTION(s)
	void SetCollisionGeometry(char* fileName, Material material, ID3D11Device* device);
	inline void SetDrawCollider(bool render) { m_RenderCollision = render; }

};

#endif

