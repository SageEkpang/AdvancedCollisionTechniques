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

class GJKCollider;
class SATCollider;

class Collider
{
protected:

	// BASE VARIABLE(s)
	Transform* m_Transform;
	Material m_Material;
	Geometry m_Geometry;
	XMFLOAT4X4* m_World;

	bool m_IsCollidable = true;
	bool m_RenderCollision = true;

	// VERTEX VARIABLE(s)
	std::vector<Vector3> m_Vertices;

public:

	// CLASS FUNCTION(s)
	Collider(Transform* transform);


	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

	virtual bool CollidesWith(Collider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) { return false; }

	virtual bool CollidesWith(SATCollider& other, CollisionManifold& out) { return false; }

	// GETTER FUNCTION(s)
	inline Transform* GetTransform() { return m_Transform; }

	inline Vector3 GetPosition() const { return m_Transform->GetPosition(); }
	inline Vector3 GetScale() const { return m_Transform->GetScale(); }
	inline Vector3 GetRotation() const { return m_Transform->GetRotation(); }

	inline bool GetRenderCollision() const { return m_RenderCollision; }
	inline bool GetIsColliedable() const { return m_IsCollidable; }

	// SETTER FUNCTION(s)
	void SetIsCollidable(bool isCollidable) { m_IsCollidable = isCollidable; }
	void SetCollisionGeometry(char* fileName, Material material, ID3D11Device* device);
	inline void SetDrawCollider(bool render) { m_RenderCollision = render; }

	// HELPER
	Vector3 FindFurthestPoint(Vector3 direction); // GJK Algo Function

};

#endif

