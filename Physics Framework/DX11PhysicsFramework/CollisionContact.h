#pragma once
#ifndef COLLISION_CONTACT_H
#define COLLISION_CONTACT_H

// ABSTRACT CLASS(s)
#include "Collider.h"
#include "RigidbodyObject.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CLASS INCLUDE(s)

class CollisionContact
{
private:

	Vector3 m_ContactPoint;
	Vector3 m_ContactNormal;
	float m_Penetration;

	// NOTE: Duration Equals DeltaTime
	void ResolveVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration);
	void ResolveVelocityAlt(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration);
	void ResolveInterpenetration(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float duration);

protected:

	void ResolveCollision(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration);
	Vector3 CalculateSeparatingVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB) const;

public:

	// CLASS FUNCTION(s)
	CollisionContact();
	~CollisionContact();


	// BASE FUNCTION(s)




};

#endif