#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include "Vector3.h"

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
	ContactPoint points[4];
	int contactPointCount;
	float penetrationDepth;

	Vector3 collisionNormal;
	bool hasCollision;

	CollisionManifold(int contactPointCount = 0, ContactPoint points = ContactPoint(), Vector3 collisionNormal = Vector3())
	{
		this->contactPointCount = contactPointCount;
		*this->points = points;
		this->collisionNormal = collisionNormal;
		this->hasCollision = false;
		penetrationDepth = 0.0f;
	}
};

#endif