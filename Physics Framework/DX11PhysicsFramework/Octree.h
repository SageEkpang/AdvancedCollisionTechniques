#pragma once
#ifndef OCTREE_H
#define OCTREE_H

#include "Constants.h"
#include "Structures.h"
#include "PhysicsObject.h"

constexpr int TREE_DEPTH = 20;
constexpr int OBJECT_SPLIT = 10;

typedef struct Octant
{
	Vector3 centre;
	float halfWidth;
	Octant* child[8];
	std::list<PhysicsObject*> objList;

	Octant() = default;
	Octant(Octant& value)
	{
		this->centre = value.centre;
		this->halfWidth = value.halfWidth;
	}

}Octant;

class Octree
{
private: // PRIVATE VARIABLE(s)

	// INIT VARIABLE(s)
	Octant* m_Octant;
	int m_RegionAmount;

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

	void InsertEntity(Octant* tree, PhysicsObject* physicsEntity);
	void InsertEntities(Octant* tree, std::vector<PhysicsObject*> physicsEntities);

	void UpdateTree(Octant* tree, const float deltaTime);

	void QueryTree();
	void QueryTree(Octant* octantTree);

	void ClearOctant(int index);
	void ClearOctant(Octant* tree, int index);

	// Collision Check // NOTE: Event Dispatch 


	// GETTER FUNCTION(s)
	inline Octant* GetOctant() const { return m_Octant; }

};

#endif
