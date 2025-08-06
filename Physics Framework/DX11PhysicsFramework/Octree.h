#ifndef OCTREE_H
#define OCTREE_H

#include "Constants.h"
#include "Structures.h"
#include "PhysicsEntity.h"
#include "GameObjectEntity.h"
#include "CollisionManifold.h"

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
	std::list<GameObjectEntity*> objList;

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
	void P_InsertEntity(Octant* tree, GameObjectEntity* entity);
	void P_UpdateTree(Octant* tree, const float deltaTime);
	void P_QueryTree(Octant* tree, CollisionManifold(*CollisionFunc)(GameObjectEntity*, GameObjectEntity*), void(*ResolveFunc)(GameObjectEntity*, GameObjectEntity*, float, Vector3));
	void P_ClearOctant(Octant* tree, int index);

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Octree(Vector3 centre, float halfWidth, int stopDepth);
	~Octree();

	// BASE FUNCTION(s)
	void InsertEntity(GameObjectEntity* entity);
	void UpdateTree(const float deltaTime);
	void QueryTree(CollisionManifold (*CollisionFunc)(GameObjectEntity*, GameObjectEntity*),  void (*ResolveFunc)(GameObjectEntity*, GameObjectEntity*, float, Vector3));
	void ClearTree(int index);
};

#endif
