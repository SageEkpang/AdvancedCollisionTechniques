#ifndef COLLISION_CONTACT_H
#define COLLISION_CONTACT_H

// ABSTRACT CLASS(s)
#include "Collider.h"
#include "RigidbodyObject.h"
#include "GameObject.h"

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

	Vector3 CalculateSeparatingVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, Vector3 contactNormal) const;

public:

	// CLASS FUNCTION(s)
	CollisionContact();
	~CollisionContact();


	// BASE FUNCTION(s)

	/// <summary> Resolve Collision Code for the Collision of the Game Objects <summary>
	void ResolveCollision(GameObject* rigidbodyObjectA, GameObject* rigidbodyObjectB, float CoefRest, float duration);

	void ResolveVelocityAlt(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration, Vector3 collisionNormal);
	void ResolveInterpenetration(GameObject* gameObjectA, GameObject* gameObjectB, float penetration, Vector3 contactNormal);
	static void S_ResolveInterpenetration(GameObject* gameObjectA, GameObject* gameObjectB, float penetration, Vector3 contactNormal);

	// SETTER FUNCTION(s)

	// GETTER FUNCTION(s)

};

#endif