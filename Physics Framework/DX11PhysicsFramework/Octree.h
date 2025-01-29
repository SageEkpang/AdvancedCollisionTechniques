#pragma once
#ifndef OCTREE_H
#define OCTREE_H

#include "Constants.h"
#include "Structures.h"
#include "PhysicsObject.h"

typedef struct Octant
{
	Vector3 centre;
	float halfWidth;
	Octant* child;
	std::list<Vector3> objList;

	Octant() = default;
	Octant(Octant& value)
	{
		this->centre = value.centre;
		this->halfWidth = value.halfWidth;
		this->child = value.child;
		this->objList.insert(this->objList.end(), value.objList.begin(), value.objList.end());
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
	Octant* BuildOctree(Vector3 centre, float halfWidth, int stopDepth);


public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Octree(Vector3 centre, float halfWidth, int stopDepth);
	~Octree();

	
	void InsertEntity(PhysicsObject* physicsEntity);
	void InsertEntities(std::vector<PhysicsObject*> physicsEntities);

	void QueryTree();
	void QueryTree(Octant* octantTree);

	void ClearOctant(int index);
	void ClearOctant();


	// GETTER FUNCTION(s)
	inline Octant* GetOctant() const { return m_Octant; }


	// SETTER FUNCTION(s)


};

#endif
