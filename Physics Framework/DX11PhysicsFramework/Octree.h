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

// #include "MaterialCoefficient.h"

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

private: // PRIVATE FUNCTION(s)

	// BASE FUNCTION(s)
	Octant* BuildOctree(Vector3 centre, float halfWidth, int stopDepth);
	void P_InsertEntity(Octant* tree, GameObject* entity);
	void P_UpdateTree(Octant* tree, const float deltaTime);
	void P_QueryTree(Octant* tree, CollisionManifold(*CollisionFunc)(GameObject*, GameObject*), void(*ResolveFunc)(GameObject*, GameObject*, float, Vector3));
	void P_ClearOctant(Octant* tree, int index);

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Octree(Vector3 centre, float halfWidth, int stopDepth);
	~Octree();

	// BASE FUNCTION(s)
	void InsertEntity(GameObject* entity);
	void UpdateTree(const float deltaTime);
	void QueryTree(CollisionManifold (*CollisionFunc)(GameObject*, GameObject*),  void (*ResolveFunc)(GameObject*, GameObject*, float, Vector3));
	void ClearTree(int index);
};

#endif
