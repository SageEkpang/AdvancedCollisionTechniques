#ifndef COLLISION_CONTACT_MANAGER_H
#define COLLISION_CONTACT_MANAGER_H

// ABSTRACT CLASS(s)
#include "GameObjectEntity.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CLASS INCLUDE(s)

namespace CollisionContactManager
{
	Vector3 CalculateSeparatingVelocity(GameObjectEntity* gameObjectA, GameObjectEntity* gameObjectB);
	void ResolveCollision(GameObjectEntity* gameObjectA, GameObjectEntity* gameObjectB, float CoefRest, CollisionManifold collisionManifold);
};

#endif