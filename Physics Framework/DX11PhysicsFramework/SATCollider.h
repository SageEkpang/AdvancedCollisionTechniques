#pragma once
#ifndef SAT_COLLIDER_H
#define SAT_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"
#include "OBBCollider.h"

class SATCollider
{
private:
public:

	// CLASS FUNCTION(s)
	SATCollider();
	~SATCollider();

	// bool ObjectCollision(OBBCollider* objectA, OBBCollider* objectB, CollisionManifold& out);
	bool ObjectCollisionAlt(OBBCollider& objectA, OBBCollider& objectB, CollisionManifold& out);

	// HELPER FUNCTION(s)
	bool OverlapOnAxis(OBBCollider& obbA, OBBCollider& obbB, Vector3& axis);
};

#endif
