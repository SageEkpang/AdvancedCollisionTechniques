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
	// ResolveInterpenetration(rigidbodyObjectA, rigidbodyObjectB, duration);
}

// NOTE: This is for when objects have just collided
void CollisionContact::ResolveVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration)
{
	Vector3 t_SeperatingVelocity = CalculateSeparatingVelocity(rigidbodyObjectA, rigidbodyObjectB);

	if (t_SeperatingVelocity > 0) { return; }

	// NOTE: Calculating New Velocity
	Vector3 t_NewSeperatingVelocity = -t_SeperatingVelocity * CoefRest; // NOTE: This will be the material restiution float / double number from material
	Vector3 t_DeltaVelocity = t_NewSeperatingVelocity - t_SeperatingVelocity;

	float t_TotalInverseMass = rigidbodyObjectA->GetInverseMass();

	if (rigidbodyObjectB) { t_TotalInverseMass += rigidbodyObjectB->GetInverseMass(); }

	if (t_TotalInverseMass <= 0) return;

	Vector3 t_Impulse = t_DeltaVelocity / t_TotalInverseMass;

	Vector3 t_ImpulsePerMass = m_ContactNormal * t_Impulse;

	// Goes one way
	rigidbodyObjectA->SetVelocity(rigidbodyObjectA->GetVelocity() + t_ImpulsePerMass * rigidbodyObjectA->GetInverseMass());

	// Goes the opposite way
	if (rigidbodyObjectB) { rigidbodyObjectB->SetVelocity(rigidbodyObjectB->GetVelocity() + t_ImpulsePerMass * -rigidbodyObjectB->GetInverseMass()); }
}

// NOTE: The above function is the same as the below, but the below function factors in the accerlation of the objects as well as velocity, use below function instead
// NOTE: This is for when objects are at rest against each other, might have to have a check for this via velocity of the object in a certain direction
void CollisionContact::ResolveVelocityAlt(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration)
{
	Vector3 t_SeperatingVelocity = CalculateSeparatingVelocity(rigidbodyObjectA, rigidbodyObjectB);

	if (t_SeperatingVelocity > 0)
	{
		// If contact is seperating or stationary there is no impulse required
		return;
	}

	Vector3 t_NewSepVelocity = -t_SeperatingVelocity * CoefRest;

	Vector3 t_AccCausedVelocity = rigidbodyObjectA->GetAcceleration();

	if (rigidbodyObjectB)
	{
		t_AccCausedVelocity -= rigidbodyObjectB->GetAcceleration();
	}


	Vector3 t_AccCausedSepVelocity = t_AccCausedVelocity * m_ContactNormal * duration;

	if (t_AccCausedSepVelocity < 0)
	{
		t_NewSepVelocity += CoefRest * t_AccCausedSepVelocity;
		if (t_NewSepVelocity < 0)
		{
			t_NewSepVelocity = 0;
		}
	}

	Vector3 t_DeltaVelocity = t_NewSepVelocity - t_SeperatingVelocity;

	float t_TotalInverseMass = rigidbodyObjectA->GetInverseMass();

	if (rigidbodyObjectB)
	{
		t_TotalInverseMass += rigidbodyObjectB->GetInverseMass();
	}

	if (t_TotalInverseMass <= 0) return;


	Vector3 t_Impulse = t_DeltaVelocity / t_TotalInverseMass;

	Vector3 t_ImpulsePerMass = m_ContactNormal * t_Impulse;

	rigidbodyObjectA->ApplyImpulse(t_ImpulsePerMass * rigidbodyObjectA->GetInverseMass());
	rigidbodyObjectB->ApplyImpulse(t_ImpulsePerMass * -rigidbodyObjectB->GetInverseMass());
}

void CollisionContact::ResolveInterpenetration(GameObject* gameObjectA, GameObject* gameObjectB)
{
	if (m_Penetration <= 0) return;

	RigidbodyObject* t_RigidbodyObjectA = gameObjectA->GetRigidbody();
	RigidbodyObject* t_RigidbodyObjectB = gameObjectB->GetRigidbody();

	Transform* t_TransformA = gameObjectA->GetTransform();
	Transform* t_TransformB = gameObjectB->GetTransform();

	// Move Objects based on Inverse Mass
	float t_TotalInverseMass = t_RigidbodyObjectA->GetInverseMass();

	if (t_RigidbodyObjectB) { t_TotalInverseMass += t_RigidbodyObjectB->GetInverseMass(); }

	// If infinite mass, return (Good for stationary / static objects)
	if (t_TotalInverseMass <= 0) return;

	Vector3 t_MovePerMass = m_ContactNormal * (m_Penetration / t_TotalInverseMass);

	// TODO: Find out what particle movement is 
	Vector3 t_ParticleMovementA = t_MovePerMass * t_RigidbodyObjectA->GetInverseMass();
	Vector3 t_ParticleMovementB;

	if (t_RigidbodyObjectB) { t_ParticleMovementB = t_MovePerMass * -t_RigidbodyObjectB->GetInverseMass(); }
	else { t_ParticleMovementB = Vector3(); }

	t_TransformA->SetPosition(t_TransformA->GetPosition() + t_ParticleMovementA);

	if (t_TransformB) { t_TransformB->SetPosition(t_TransformB->GetPosition() + t_ParticleMovementB); }
}

Vector3 CollisionContact::CalculateSeparatingVelocity(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB) const
{
	Vector3 t_RelativeVelocity = rigidbodyObjectA->GetVelocity();

	if (rigidbodyObjectB)
	{
		t_RelativeVelocity -= rigidbodyObjectB->GetVelocity();
	}

	return t_RelativeVelocity * m_ContactNormal;
}
