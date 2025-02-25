#ifndef SAT_COLLIDER_H
#define SAT_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"
#include "OBBCollider.h"
#include "GameObject.h"

class SATCollider
{
public:

	// CLASS FUNCTION(s)
	SATCollider();
	~SATCollider();

	// BASE FUNCTION(s)
	CollisionManifold SATCollision(GameObject& objectA, GameObject& objectB);
	static CollisionManifold S_SATCollision(GameObject* objectA, GameObject* objectB);

	// HELPER FUNCTION(s)
	static bool OverlapOnAxis(GameObject& satA, GameObject& satB, Vector3& axis);
	static Interval GetIntervalOr(GameObject& sat, Vector3& axis);
};

#endif
