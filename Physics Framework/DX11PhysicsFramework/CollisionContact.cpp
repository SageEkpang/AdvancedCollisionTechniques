#include "CollisionContact.h"

CollisionContact::CollisionContact()
{


}

CollisionContact::~CollisionContact()
{


}

void CollisionContact::ResolveCollision(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration)
{
	// ResolveVelocityAlt(rigidbodyObjectA, rigidbodyObjectB, CoefRest, duration);
	// ResolveInterpenetration(rigidbodyObjectA, rigidbodyObjectB);
}

// NOTE: The above function is the same as the below, but the below function factors in the accerlation of the objects as well as velocity, use below function instead
// NOTE: This is for when objects are at rest against each other, might have to have a check for this via velocity of the object in a certain direction
void CollisionContact::ResolveVelocityAlt(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration, Vector3 collisionNormal)
{
	// Find the velocity in the direction of the contact
	Vector3 t_SeperatingVelocity = CalculateSeparatingVelocity(rigidbodyObjectA, rigidbodyObjectB, collisionNormal);

	// Check if the Collision needs to be resolved 
	if (t_SeperatingVelocity > 0)
	{
		// If contact is seperating or stationary there is no impulse required
		return;
	}

	// Calculate new seperating Velocity
	Vector3 t_NewSepVelocity = -t_SeperatingVelocity * CoefRest;

	// Check the Velocity buildup due to Acceleration Only
	Vector3 t_AccCausedVelocity = rigidbodyObjectA->GetAcceleration();
	if (rigidbodyObjectB) { t_AccCausedVelocity -= rigidbodyObjectB->GetAcceleration(); }

	Vector3 t_AccCausedSepVelocity = t_AccCausedVelocity * collisionNormal * duration;

	// If we have got a closing velocity due to acceleration buildup, remove it from the new separating velocity
	if (t_AccCausedSepVelocity < 0)
	{
		t_NewSepVelocity += CoefRest * t_AccCausedSepVelocity;

		// Make sure we haven't removed more than was there to remove
		if (t_NewSepVelocity < 0)
		{
			t_NewSepVelocity = 0;
		}
	}

	// Calculate a new Delta Velocity
	Vector3 t_DeltaVelocity = t_NewSepVelocity - t_SeperatingVelocity;

	// Those with a higher mass get a less effect to there mass and inverse mass
	float t_TotalInverseMass = rigidbodyObjectA->GetInverseMass();
	if (rigidbodyObjectB) { t_TotalInverseMass += rigidbodyObjectB->GetInverseMass(); }

	// If all particles have infinite mass, then impulses have no effect
	if (t_TotalInverseMass <= 0) return;

	// Calculate the impulse to apply
	Vector3 t_Impulse = t_DeltaVelocity / t_TotalInverseMass;

	// Apply impulses: they are applied in the direction of the contact, and are proportional to the inverse mass
	Vector3 t_ImpulsePerMass = collisionNormal * t_Impulse;
	float dampening = 0.9;

	rigidbodyObjectA->ApplyImpulse(t_ImpulsePerMass * rigidbodyObjectA->GetInverseMass() * dampening);
	rigidbodyObjectB->ApplyImpulse(t_ImpulsePerMass * -rigidbodyObjectB->GetInverseMass() * dampening);
}

void CollisionContact::ResolveInterpenetration(GameObject* gameObjectA, GameObject* gameObjectB, float penetration, Vector3 contactNormal)
{
	// NOTE: If no penetration, skip this step
	if (penetration <= 0) return;

	// NOTE: Init Variables
	RigidbodyObject* t_RigidbodyObjectA = gameObjectA->GetRigidbody();
	RigidbodyObject* t_RigidbodyObjectB = gameObjectB->GetRigidbody();

	Transform* t_TransformA = gameObjectA->GetTransform();
	Transform* t_TransformB = gameObjectB->GetTransform();

	// Move Objects based on Inverse Mass
	float t_TotalInverseMass = t_RigidbodyObjectA->GetInverseMass();
	if (t_RigidbodyObjectB) { t_TotalInverseMass += t_RigidbodyObjectB->GetInverseMass(); }

	// If infinite mass, return (Good for stationary / static objects)
	if (t_TotalInverseMass <= 0) return;


	// Find the amount of penetration resolution per unit of inverse mass
	Vector3 t_MovePerMass = contactNormal * (penetration / t_TotalInverseMass);

	// Calculate Movement Amount
	Vector3 t_ParticleMovementA = t_MovePerMass * t_RigidbodyObjectA->GetInverseMass();
	Vector3 t_ParticleMovementB;

	if (t_RigidbodyObjectB) { t_ParticleMovementB = t_MovePerMass * -t_RigidbodyObjectB->GetInverseMass(); }
	else { t_ParticleMovementB = Vector3(); }


	// Apply Penetration Resolution
	t_TransformA->SetPosition(t_TransformA->GetPosition() + t_ParticleMovementA);
	if (t_TransformB) { t_TransformB->SetPosition(t_TransformB->GetPosition() + t_ParticleMovementB); }
}

Vector3 CollisionContact::CalculateSeparatingVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, Vector3 contactNormal) const
{
	Vector3 t_RelativeVelocity = rigidbodyObjectA->GetVelocity();
	if (rigidbodyObjectB) { t_RelativeVelocity -= rigidbodyObjectB->GetVelocity(); }

	return t_RelativeVelocity * contactNormal;
}
