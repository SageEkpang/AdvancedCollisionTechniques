#ifndef COLLISION_CONTACT_H
#define COLLISION_CONTACT_H

// ABSTRACT CLASS(s)
#include "GameObjectEntity.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CLASS INCLUDE(s)

class CollisionContact
{
private:

	CollisionManifold m_CollisionManifold;
	Vector3 m_ContactPoint;

protected:

	Vector3 CalculateSeparatingVelocity(GameObjectEntity* gameObjectA, GameObjectEntity* gameObjectB);

public:

	// CLASS FUNCTION(s)
	CollisionContact();
	~CollisionContact();

	// BASE FUNCTION(s)

	/// <summary> Resolve Collision Code for the Collision of the Game Objects <summary>
	void ResolveCollision(GameObjectEntity* rigidbodyObjectA, GameObjectEntity* rigidbodyObjectB, float CoefRest, float penetration, Vector3 contactNormal);

	// SETTER FUNCTION(s)

	// GETTER FUNCTION(s)

};

#endif