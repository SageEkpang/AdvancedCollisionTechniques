#include "MassAggregate.h"
#include <cmath>

MassAggregate::MassAggregate(char* filePath, Vector3 position, float mass, int size, ID3D11Device* device)
{
	// NOTE: Collision Contact
	m_CollisionContact = new CollisionContact();

	// NOTE: Physics Variables
	m_Mass = mass;
	m_Size = size;

	// NOTE: Fill Vertex Data
	std::vector<Vector3> t_TempVec = MeshLoader::LoadObj(filePath);

	// NOTE: Fill array with the different mesh load values
	for (int i = 0; i < t_TempVec.size(); ++i)
	{
		// NOTE: Set Default for Scale and Rotation
		Transform* t_TempTrans = new Transform();
		t_TempTrans->SetScale(0.2f, 0.2f, 0.2f);
		t_TempTrans->SetRotation(0.f, 0.f, 0.f);

		// NOTE: Calculate World Position Based on the Vertex Data
		// Vector3 t_VecPos = (t_TempVec[i] * size) + m_Transform->GetPosition();
		Vector3 t_VecPos = (t_TempVec[i] * size) + position;
		t_TempTrans->SetPosition(t_VecPos);

		// NOTE: Set and Push data into the Array and Buffer
		Particle* t_TempPart = new Particle(t_TempTrans, mass, device);
		m_MassPoints.push_back(t_TempPart);
	}
}

MassAggregate::~MassAggregate()
{
	ClearParticle();
}

void MassAggregate::Update(float deltaTime)
{
	// NOTE: Update Particles
	for (auto& v : m_MassPoints)
	{
		// NOTE: The particle does not have mass, so do not do anything with it
		if (v->GetMass() <= 0) { return; }

		// NOTE: Apply Gravity to Objects
		v->ApplyImpulse(v->GetGravity() * deltaTime);
		
		// NOTE: Resolve Position for the Floor // NOTE: "0" = floor
		if (v->GetPosition().y < 0)
		{
			v->SetPosition(Vector3(v->GetPosition().x, 0, v->GetPosition().z));
			float t_Dampening = 0.01f;
			v->SetVelocity(Vector3(v->GetVelocity().x, -v->GetVelocity().y * t_Dampening, v->GetVelocity().z));
		}

		v->Update(deltaTime);
	}

	// NOTE: Rod Code
	#pragma region MyRegion

	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		for (int j = 0; j < m_MassPoints.size(); ++j)
		{
			if (i == j) { continue; }
			
			// NOTE: "Current Length" is just the distance between the two vectors magnitude
			float t_CurrentLength = Vector::Magnitude(m_MassPoints[i]->GetPosition() - m_MassPoints[j]->GetPosition()) / 2;
			
			// NOTE: Skip Current Iteration
			if (t_CurrentLength == m_Size) { continue; }

			CollisionManifold t_ColManifold = CollisionManifold();

			// NOTE: Normal Calculation
			Vector3 t_Normal = m_MassPoints[j]->GetPosition() - m_MassPoints[i]->GetPosition();
			
			float t_Target = m_Size; // NOTE: This is the "distance" that the rods need to be at
			Vector3 t_Disperse = m_MassPoints[i]->GetPosition() - m_MassPoints[j]->GetPosition();
			float t_Distance = t_CurrentLength;

			Vector3 t_NewNormal = t_Disperse / t_Distance;
			float t_Delta = t_Target - t_Distance;

			Vector3 t_TargetPosA = m_MassPoints[i]->GetPosition() + t_Delta * t_NewNormal.Normalise();
			Vector3 t_TargetPosB = m_MassPoints[j]->GetPosition() - t_Delta * t_NewNormal.Normalise();

			m_MassPoints[i]->SetPosition(t_TargetPosA);
			m_MassPoints[j]->SetPosition(t_TargetPosB);


			//if (t_CurrentLength >= m_Size)
			//{
			//	t_ColManifold.collisionNormal = t_Normal.Normalise();
			//	t_ColManifold.penetrationDepth = t_CurrentLength - m_Size;

			//	ResolveVelocity(m_MassPoints[i], m_MassPoints[j], deltaTime, t_ColManifold.collisionNormal);
			//	ResolveInterpenetrationAlt(m_MassPoints[i], m_MassPoints[j], t_ColManifold.penetrationDepth, deltaTime, t_ColManifold.collisionNormal);
			//}
			//else
			//{
			//	t_ColManifold.collisionNormal = -t_Normal.Normalise();
			//	t_ColManifold.penetrationDepth = m_Size - t_CurrentLength;

			//	ResolveVelocity(m_MassPoints[i], m_MassPoints[j], deltaTime, t_ColManifold.collisionNormal);
			//	ResolveInterpenetrationAlt(m_MassPoints[i], m_MassPoints[j], t_ColManifold.penetrationDepth, deltaTime, t_ColManifold.collisionNormal);
			//}
		}
	}

	#pragma endregion
}

void MassAggregate::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	// pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	for (auto& v : m_MassPoints)
	{
		v->Draw(constantBufferData, constBuff, pImmediateContext, device, Vector3(1, 0, 0));
	}
}

void MassAggregate::ResolveVelocity(Particle* particleA, Particle* particleB, float duration, Vector3 collisionNormal)
{
	// Find the velocity in the direction of the contact
	Vector3 t_SeperatingVelocity = CalculateSeparatingVelocity(particleA, particleB, collisionNormal);

	// Check if the Collision needs to be resolved 
	// If contact is seperating or stationary there is no impulse required
	if (t_SeperatingVelocity > 0) { return; }

	// Calculate new seperating Velocity
	Vector3 t_NewSepVelocity = -t_SeperatingVelocity;

	// Calculate a new Delta Velocity
	Vector3 t_DeltaVelocity = t_NewSepVelocity - t_SeperatingVelocity;

	// Those with a higher mass get a less effect to there mass and inverse mass
	float t_TotalInverseMass = particleA->GetInverseMass() * GRAVITY_EARTH;
	if (particleB) { t_TotalInverseMass += particleB->GetInverseMass() * GRAVITY_EARTH; }

	// If all particles have infinite mass, then impulses have no effect
	if (t_TotalInverseMass <= 0) return;

	// Calculate the impulse to apply
	Vector3 t_Impulse = t_DeltaVelocity / t_TotalInverseMass;

	// Apply impulses: they are applied in the direction of the contact, and are proportional to the inverse mass
	Vector3 t_ImpulsePerMass = collisionNormal * t_Impulse * 2;

	particleA->SetVelocity(particleA->GetVelocity() + t_ImpulsePerMass * -particleA->GetInverseMass());

	if (particleB)
	{
		particleB->SetVelocity(particleB->GetVelocity() + t_ImpulsePerMass * -particleB->GetInverseMass());
	}
}

void MassAggregate::ResolveInterpenetration(Particle* particleA, Particle* particleB, float penetration, float duration, Vector3 collisionNormal)
{
	// NOTE: If no penetration, skip this step
	if (penetration <= 0) return;

	// Move Objects based on Inverse Mass
	float t_TotalInverseMass = particleA->GetInverseMass();
	if (particleB) { t_TotalInverseMass += particleB->GetInverseMass(); }

	// If infinite mass, return (Good for stationary / static objects)
	if (t_TotalInverseMass <= 0) return;


	// Find the amount of penetration resolution per unit of inverse mass
	Vector3 t_MovePerMass = collisionNormal * (penetration / t_TotalInverseMass);

	// Calculate Movement Amount
	Vector3 t_ParticleMovementA = t_MovePerMass * particleA->GetInverseMass();
	Vector3 t_ParticleMovementB;

	if (particleB) { t_ParticleMovementB = t_MovePerMass * -particleB->GetInverseMass(); }
	else { t_ParticleMovementB = Vector3(); }


	// Apply Penetration Resolution
	particleA->GetTransform()->SetPosition(particleA->GetTransform()->GetPosition() + t_ParticleMovementA);
	if (particleB) { particleB->GetTransform()->SetPosition((particleB->GetTransform()->GetPosition() + t_ParticleMovementB)); }
}

void MassAggregate::ResolveInterpenetrationAlt(Particle* particleA, Particle* particleB, float penetration, float duration, Vector3 collisionNormal)
{
	if (penetration <= 0) return;

	// Move Objects based on Inverse Mass
	float t_TotalInverseMass = particleA->GetInverseMass();
	t_TotalInverseMass += particleB->GetInverseMass();

	// If infinite mass, return (Good for stationary / static objects)
	if (t_TotalInverseMass <= 0) return;

	// Find the amount of penetration resolution per unit of inverse mass
	Vector3 t_MovePerMass = collisionNormal * (penetration / t_TotalInverseMass);

	// Calculate Movement Amount
	Vector3 t_ParticleMovementA = t_MovePerMass * particleA->GetInverseMass();
	Vector3 t_ParticleMovementB = t_MovePerMass * -particleB->GetInverseMass();

	// Apply Penetration Resolution
	particleA->GetTransform()->SetPosition(particleA->GetTransform()->GetPosition() + t_ParticleMovementA);
	particleB->GetTransform()->SetPosition(particleB->GetTransform()->GetPosition() + t_ParticleMovementB);
}

Vector3 MassAggregate::CalculateSeparatingVelocity(Particle* particleA, Particle* particleB, Vector3 contactNormal)
{
	Vector3 t_RelativeVelocity = particleA->GetVelocity();
	if (particleB) { t_RelativeVelocity -= particleB->GetVelocity(); }
	return t_RelativeVelocity * contactNormal;
}

void MassAggregate::ClearParticle()
{
	// NOTE: Clear Mass Points
	if (!m_MassPoints.empty())
	{
		std::vector<Particle*>::iterator itr;
		for (itr = m_MassPoints.begin(); itr != m_MassPoints.end(); ++itr) { delete* itr; }

		m_MassPoints.clear();
	}
}