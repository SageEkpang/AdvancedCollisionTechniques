#ifndef SAT_COLLIDER_H
#define SAT_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"
#include "OBBCollider.h"
#include "GameObjectEntity.h"

class SATCollider : public ColliderEntity
{
public:

	// CLASS FUNCTION(s)
	//SATCollider();
	//~SATCollider();

	//// BASE FUNCTION(s)
	//CollisionManifold SATCollision(GameObjectEntity& objectA, GameObjectEntity& objectB);
	//static CollisionManifold S_SATCollision(GameObjectEntity* objectA, GameObjectEntity* objectB);

	//// HELPER FUNCTION(s)
	//static bool OverlapOnAxis(GameObjectEntity& satA, GameObjectEntity& satB, Vector3& axis);
	//static Interval GetIntervalOr(GameObjectEntity& sat, Vector3& axis);
};

#endif
