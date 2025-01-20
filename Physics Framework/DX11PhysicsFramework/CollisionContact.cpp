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
	// TODO: Resolve Interpenetration (Might be another variable to do with the penetration)

}

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
