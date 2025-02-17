#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Structures.h"
#include "Constants.h"
#include "Transform.h"
#include "Vector.h"

#include "OBJLoader.h"
#include "MeshLoader.h"

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

	typedef std::pair<ColliderType, ColliderType> Col2;
	typedef CollisionManifold (*ColFunc)(Collider*, Collider*, CollisionManifold&);

	// BASE VARIABLE(s)
	Transform* m_Transform;
	Material m_Material;
	Geometry m_Geometry;
	XMFLOAT4X4* m_World;
	ColliderType m_ColliderType = ColliderType::COLLIDER_NONE;

	bool m_IsCollidable = true;
	bool m_RenderCollision = true;
	float m_Radius = 0;

	// VERTEX VARIABLE(s)
	std::vector<Vector3> m_Vertices;

	// COLLIDER VARIABLE(s)
	// std::unordered_map<Col2, ColFunc> m_MapColliderFunctions;

public:

	// CLASS FUNCTION(s)
	Collider(Transform* transform);

	/// <summary> Box / PlaneCollider </summary>
	Collider(Transform* transform, float width, float length, float height, bool isPlane) { }

	/// <summary> Sphere Collider </summary>
	Collider(Transform* transform, float radius) { }

	/// <summary> OBB (Oriented Bounding Box) Collider </summary>
	Collider(Transform* transform, float width, float length, float height, Vector3 rotation) { }



	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

	virtual bool CollidesWith(Collider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(SphereCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(BoxCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(PlaneCollider& other, CollisionManifold& out) { return false; }

	virtual bool CollidesWith(OBBCollider& other, CollisionManifold& out) { return false; }
	virtual bool CollidesWith(SATCollider& other, CollisionManifold& out) { return false; }



	// NEW FUNCTION(s)

	// SPHERE
	// CollisionManifold SphereToSphereCol(Collider* objectA, Collider* objectB, CollisionManifold& out);

	// bool ObjectCollision(Collider* objectA, Collider* objectB, CollisionManifold& out);



	// GETTER FUNCTION(s)
	inline Transform* GetTransform() { return m_Transform; }

	inline Vector3 GetPosition() const { return m_Transform->GetPosition(); }
	inline Vector3 GetScale() const { return m_Transform->GetScale(); }
	inline Vector3 GetRotation() const { return m_Transform->GetRotation(); }

	inline bool GetRenderCollision() const { return m_RenderCollision; }
	inline bool GetIsColliedable() const { return m_IsCollidable; }

	inline ColliderType GetColliderType() const { return m_ColliderType; }
	inline float GetRadius() const { return m_Radius; }


	// SETTER FUNCTION(s)
	void SetIsCollidable(bool isCollidable) { m_IsCollidable = isCollidable; }
	void SetCollisionGeometry(char* fileName, Material material, ID3D11Device* device);
	inline void SetDrawCollider(bool render) { m_RenderCollision = render; }

	

	// HELPER
	Vector3 FindFurthestPoint(Vector3 direction); // GJK Algo Function
	Vector3 SphereNearestPoint(Vector3 point);

	// TODO: Make a function that updates the verticese within this field
	/// <summary> NOTE: This needs to take a file path for computing the points to draw </summary>
	void FillVerticesArray(char* path, Transform* objectTransform);
};

#endif

