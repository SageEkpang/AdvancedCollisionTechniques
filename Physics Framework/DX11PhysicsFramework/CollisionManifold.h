#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include "Vector3.h"
#include <vector>

class GameObjectEntity;

struct CollisionManifold
{
	// NOTE: Ray Variable(s)
	GameObjectEntity* hitObject;
	GameObjectEntity* ownerObject;
	float lineLength;
	Vector3 origin;
	Vector3 direction;

	// NOTE: General Variable(s)
	Vector3 collisionNormal;
	int contactPointCount;
	float penetrationDepth;
	bool hasCollision;

	CollisionManifold(int contactPointCount = 0, Vector3 collisionNormal = Vector3())
	{
		this->contactPointCount = contactPointCount;
		this->collisionNormal = collisionNormal;
		this->hasCollision = false;
		penetrationDepth = 0.0f;
	}
};

#endif