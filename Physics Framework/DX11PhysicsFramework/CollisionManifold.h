#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include "Vector3.h"
#include <vector>

class GameObjectEntity;

struct ContactPoint
{
	GameObjectEntity* pointObject;
	Vector3 collisionNormal;
	int index;
	float penetrationDepth;
	bool hasCollision;
	int contactPointCount;

	ContactPoint(int contactPointCount = 0, Vector3 collisionNormal = Vector3())
	{
		this->contactPointCount = contactPointCount;
		this->collisionNormal = collisionNormal;
		this->hasCollision = false;
		index = 0;
		penetrationDepth = 0.0f;
		pointObject = nullptr;
	}
};

struct CollisionManifold
{
	std::vector<ContactPoint> points;
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