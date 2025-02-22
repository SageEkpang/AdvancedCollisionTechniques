#pragma once
#ifndef OCTREE_H
#define OCTREE_H

#include "Constants.h"
#include "Structures.h"
#include "PhysicsObject.h"
#include "GameObject.h"

#include "SATCollider.h"
#include "EPACollider.h"
#include "GJKCollider.h"

#include "Timer.h"

constexpr int TREE_DEPTH = 20;
constexpr int OBJECT_SPLIT = 10;

struct Octant
{
	Vector3 centre;
	float halfWidth;
	Octant* child[8]{};
	std::list<GameObject*> objList;

	Octant() = default;
	Octant(Octant& value)
	{
		this->centre = value.centre;
		this->halfWidth = value.halfWidth;
	}

};

class Octree
{
private: // PRIVATE VARIABLE(s)

	// INIT VARIABLE(s)
	Octant* m_Octant;
	int m_RegionAmount;

	SATCollider* m_SATCollider;
	GJKCollider* m_GJKCollider;
	EPACollider* m_EPACollider;

private: // PRIVATE FUNCTION(s)

	// BASE FUNCTION(s)


public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Octree();
	Octree(int regionAmount);
	Octree(Vector3 centre, float halfWidth, int stopDepth);
	~Octree();


	// BASE FUNCTION(s)
	Octant* BuildOctree(Vector3 centre, float halfWidth, int stopDepth);

	void InsertEntity(Octant* tree, GameObject* physicsEntity);
	void InsertEntities(Octant* tree, std::vector<GameObject*> physicsEntities);

	void UpdateTree(Octant* tree, const float deltaTime);

	void QueryTree();
	void QueryTree(Octant* octantTree, int i);

	void ClearOctant(int index);
	void ClearOctant(Octant* tree, int index);

	void ResolveCollision(RigidbodyObject* objectA, RigidbodyObject* objectB, float CoefRest, Vector3 normal);

	// GETTER FUNCTION(s)
	inline Octant* GetOctant() const { return m_Octant; }

};

#endif
