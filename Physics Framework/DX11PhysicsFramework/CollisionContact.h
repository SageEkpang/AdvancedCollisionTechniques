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
	Vector3 m_ContactNormal;
	float m_Penetration;

	// NOTE: Duration Equals DeltaTime
	void ResolveVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration);

protected:

	Vector3 CalculateSeparatingVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB) const;

public:

	// CLASS FUNCTION(s)
	CollisionContact();
	~CollisionContact();


	// BASE FUNCTION(s)

	/// <summary> Resolve Collision Code for the Collision of the Game Objects
	void ResolveCollision(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration);

	void ResolveVelocityAlt(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration);
	void ResolveInterpenetration(GameObject* gameObjectA, GameObject* gameObjectB);

	// SETTER FUNCTION(s)
	void SetContactNormal(Vector3 normal) { m_ContactNormal = normal; }
	void SetPenetration(float penetration) { m_Penetration = penetration; }

	// GETTER FUNCTION(s)
	inline Vector3 GetContactNormal() { return m_ContactNormal; }
	inline float GetPenetration() { return m_Penetration; }

};

#endif