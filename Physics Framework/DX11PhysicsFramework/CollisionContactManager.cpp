#include "CollisionContactManager.h"

namespace CollisionContactManager
{
	namespace
	{
		std::unordered_set<GameObjectEntity*> gameObjectAList;
		std::unordered_set<GameObjectEntity*> gameObjectBList;
	}

	void ResolveCollision(GameObjectEntity* gameObjectA, GameObjectEntity* gameObjectB, float CoefRest, CollisionManifold collisionManifold)
	{
		gameObjectAList = gameObjectA->FindChildComponent<ColliderEntity>()->GetCollisionSet();
		gameObjectBList = gameObjectB->FindChildComponent<ColliderEntity>()->GetCollisionSet();

		for (auto itrA = gameObjectAList.begin(); itrA != gameObjectAList.end(); ++itrA)
		{
			for (auto itrB = gameObjectBList.begin(); itrB != gameObjectBList.end(); ++itrB)
			{
				// NOTE: Move the object out of the other object first and then apply the force to the object
				Vector3 t_SeperatingVelocity = CollisionContactManager::CalculateSeparatingVelocity(*itrA, *itrB);

				// If there is no need for seperating velocity, then we do not need to run the function
				if (t_SeperatingVelocity > Vector3(0.f, 0.f, 0.f)) { return; }

				// NOTE: If the rigidbody 2D component is not on the object and they are colliding, treat it as if infinite mass is applied
				float m_RigidbodyObjectAMass = FLT_MAX;
				float m_RigidbodyObjectAInverseMass = 1.f / FLT_MAX;

				float m_RigidbodyObjectBMass = FLT_MAX;
				float m_RigidbodyObjectBInverseMass = 1.f / FLT_MAX;

				if ((*itrA)->HasComponent<Rigidbody3DObject>())
				{
					m_RigidbodyObjectAMass = (*itrA)->GetComponent<Rigidbody3DObject>()->m_Mass;
					m_RigidbodyObjectAInverseMass = (*itrA)->GetComponent<Rigidbody3DObject>()->GetInverseMass();

					if ((*itrA)->GetComponent<Rigidbody3DObject>()->m_RigidbodyMovementType == Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_STATIC)
					{
						m_RigidbodyObjectAMass = FLT_MAX;
						m_RigidbodyObjectAInverseMass = 1.f / FLT_MAX;
					}
				}

				if ((*itrB)->HasComponent<Rigidbody3DObject>())
				{
					m_RigidbodyObjectBMass = (*itrB)->GetComponent<Rigidbody3DObject>()->m_Mass;
					m_RigidbodyObjectBInverseMass = (*itrB)->GetComponent<Rigidbody3DObject>()->GetInverseMass();

					if ((*itrB)->GetComponent<Rigidbody3DObject>()->m_RigidbodyMovementType == Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_STATIC)
					{
						m_RigidbodyObjectBMass = FLT_MAX;
						m_RigidbodyObjectBInverseMass = 1.f / FLT_MAX;
					}
				}

				// NOTE: Resolution Calculations Starting
				float t_TotalInverseMass = m_RigidbodyObjectAInverseMass;
				t_TotalInverseMass += m_RigidbodyObjectBInverseMass;

				if (t_TotalInverseMass == 0) { return; }

				// Find by how much to move the entity
				Vector3 t_MovePerMass = collisionManifold.collisionNormal * (collisionManifold.penetrationDepth / t_TotalInverseMass);
				Vector3 t_MoveOutA = t_MovePerMass * m_RigidbodyObjectAInverseMass;
				Vector3 t_MoveOutB = -t_MovePerMass * m_RigidbodyObjectBInverseMass;

				float InverseA = m_RigidbodyObjectAInverseMass;
				float InverseB = m_RigidbodyObjectBInverseMass;

				// NOTE: See if the objects are moving into each other
				float t_VelocityAlongNormal = 
					t_SeperatingVelocity.x * collisionManifold.collisionNormal.x + 
					t_SeperatingVelocity.y * collisionManifold.collisionNormal.y + 
					t_SeperatingVelocity.z * collisionManifold.collisionNormal.z;

				// NOTE: Calculate the bounce of the objects based off their inverse mass and normal
				float impMag = (-(1 + CoefRest) * t_VelocityAlongNormal) / (InverseA + InverseB);

				// NOTE: Velocity / Position Solving
				if ((*itrA)->HasComponent<Rigidbody3DObject>()
					&& (*itrA)->GetComponent<Rigidbody3DObject>()->m_RigidbodyMovementType == Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC)
				{
					// NOTE: Seperate the 2 objects away from each other if they are still interpentrating
					if (collisionManifold.penetrationDepth != 0) { (*itrA)->m_Transform.m_Position += t_MoveOutA; }

					// NOTE: If velocity along the normal is greater than 0, we want to resolve the collision
					if (t_VelocityAlongNormal > 0) { return; }
					float impulseX = impMag * collisionManifold.collisionNormal.x;
					float impulseY = impMag * collisionManifold.collisionNormal.y;
					float impulseZ = impMag * collisionManifold.collisionNormal.z;

					// NOTE: Apply calculation to the new objects
					(*itrA)->GetComponent<Rigidbody3DObject>()->ApplyImpulseX(impulseX / (*itrA)->GetComponent<Rigidbody3DObject>()->m_Mass);
					(*itrA)->GetComponent<Rigidbody3DObject>()->ApplyImpulseY(impulseY / (*itrA)->GetComponent<Rigidbody3DObject>()->m_Mass);
					(*itrA)->GetComponent<Rigidbody3DObject>()->ApplyImpulseZ(impulseZ / (*itrA)->GetComponent<Rigidbody3DObject>()->m_Mass);
				}

				if ((*itrB)->HasComponent<Rigidbody3DObject>()
					&& (*itrB)->GetComponent<Rigidbody3DObject>()->m_RigidbodyMovementType == Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC)
				{
					// NOTE: Seperate the 2 objects away from each other if they are still interpentrating
					if (collisionManifold.penetrationDepth != 0) { (*itrB)->m_Transform.m_Position += t_MoveOutB; }

					// NOTE: If velocity along the normal is greater than 0, we want to resolve the collision
					if (t_VelocityAlongNormal > 0) { return; }
					float impulseX = impMag * collisionManifold.collisionNormal.x;
					float impulseY = impMag * collisionManifold.collisionNormal.y;
					float impulseZ = impMag * collisionManifold.collisionNormal.z;

					// NOTE: Apply calculation to the new objects
					(*itrB)->GetComponent<Rigidbody3DObject>()->ApplyImpulseX(-1 * impulseX / (*itrB)->GetComponent<Rigidbody3DObject>()->m_Mass);
					(*itrB)->GetComponent<Rigidbody3DObject>()->ApplyImpulseY(-1 * impulseY / (*itrB)->GetComponent<Rigidbody3DObject>()->m_Mass);
					(*itrB)->GetComponent<Rigidbody3DObject>()->ApplyImpulseZ(-1 * impulseZ / (*itrB)->GetComponent<Rigidbody3DObject>()->m_Mass);
				}
			}
		}
	}

	Vector3 CalculateSeparatingVelocity(GameObjectEntity* gameObjectA, GameObjectEntity* gameObjectB)
	{
		Vector3 t_RelativeVelocity = Vector3();

		if (!gameObjectA->HasComponent<Rigidbody3DObject>())
		{
			t_RelativeVelocity = Vector3(0.f, 0.f, 0.f);
		}
		else
		{
			t_RelativeVelocity = gameObjectA->GetComponent<Rigidbody3DObject>()->m_Velocity;
		}

		if (!gameObjectB->HasComponent<Rigidbody3DObject>())
		{
			t_RelativeVelocity -= Vector3(0.f, 0.f, 0.f);
		}
		else
		{
			t_RelativeVelocity -= gameObjectB->GetComponent<Rigidbody3DObject>()->m_Velocity;
		}

		return t_RelativeVelocity;
	}
};





