#include "CollisionContact.h"

CollisionContact::CollisionContact()
{




}

CollisionContact::~CollisionContact()
{
	


}


void CollisionContact::ResolveCollision(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration)
{
	ResolveVelocity(rigidbodyObjectA, rigidbodyObjectB, CoefRest, duration);
	ResolveInterpenetration(rigidbodyObjectA, rigidbodyObjectB, duration);

}
// TODO: Need to make the rods for the collision code
// At Collision
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

// At Rest
void CollisionContact::ResolveVelocityAlt(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float CoefRest, float duration)
{
	Vector3 t_SeperatingVelocity = CalculateSeparatingVelocity(rigidbodyObjectA, rigidbodyObjectB);

	if (t_SeperatingVelocity > 0)
	{
		// If contact is seperatingt or stationary there is no impulse required
		return;
	}

	Vector3 t_NewSepVelocity = -t_SeperatingVelocity * CoefRest;

	Vector3 t_AccCausedVelocity = rigidbodyObjectA->GetAcceleration();

	if (rigidbodyObjectB)
	{
		t_AccCausedVelocity -= rigidbodyObjectB->GetAcceleration();
	}


	Vector3 t_AccCausedSepVelocity = t_AccCausedVelocity * m_ContactNormal * duration; // TODO: May need to pass in contact normal to the function via the collision code

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

	rigidbodyObjectA->SetVelocity(rigidbodyObjectA->GetVelocity() + t_ImpulsePerMass * rigidbodyObjectA->GetInverseMass());

	if (rigidbodyObjectB)
	{
		rigidbodyObjectB->SetVelocity(rigidbodyObjectB->GetVelocity() + t_ImpulsePerMass * -rigidbodyObjectB->GetInverseMass());
	}


}

void CollisionContact::ResolveInterpenetration(RigidbodyObject* rigidbodyObjectA, RigidbodyObject* rigidbodyObjectB, float duration)
{
	if (m_Penetration <= 0) return;

	// Move Objects based on Inverse Mass
	float t_TotalInverseMass = rigidbodyObjectA->GetInverseMass();

	if (rigidbodyObjectB) { t_TotalInverseMass += rigidbodyObjectB->GetInverseMass(); }

	// If infinite mass, return (Good for stationary / static objects)
	if (t_TotalInverseMass <= 0) return;

	Vector3 t_MovePerMass = m_ContactNormal * (m_Penetration / t_TotalInverseMass);

	// TODO: Find out what particle movement is 
	Vector3 t_ParticleMovementA = t_MovePerMass * rigidbodyObjectA->GetInverseMass();
	Vector3 t_ParticleMovementB;

	if (rigidbodyObjectB) { t_ParticleMovementB = t_MovePerMass * -rigidbodyObjectB->GetInverseMass(); }
	else { t_ParticleMovementB = Vector3(); }


	rigidbodyObjectA->GetTransform()->SetPosition(rigidbodyObjectA->GetTransform()->GetPosition() + t_ParticleMovementA);

	if (rigidbodyObjectB) { rigidbodyObjectB->GetTransform()->SetPosition(rigidbodyObjectB->GetTransform()->GetPosition() + t_ParticleMovementB); }


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
