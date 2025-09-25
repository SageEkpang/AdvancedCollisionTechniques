#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include "Vector3.h"
#include <vector>

class GameObjectEntity;

struct ContactPoint
{
	Vector3 position;
	float penetrationDepth;

	ContactPoint()
	{
		position = Vector3();
		penetrationDepth = 0.0f;
	}
};

struct CollisionManifold
{
	std::vector<GameObjectEntity*> points; // NOTE: Purely used for the entities

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
		points.clear();
	}
};

#endif