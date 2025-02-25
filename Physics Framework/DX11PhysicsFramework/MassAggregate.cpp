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
		t_TempTrans->SetScale(0.1f, 0.1f, 0.1f);
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
	if (GetAsyncKeyState(VK_RETURN))
	{
		for (auto& v : m_MassPoints)
		{
			v->ApplyImpulse(Vector3(0, 1, 0));
		}
	}

	bool t_ApplyGravity = false;
	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		// NOTE: Checks if the particle mass is not 0
		if (m_MassPoints[i]->GetMass() <= 0) { return; }

		// NOTE: Check if all the mass points are in the air or if one is touching the ground
		for (int j = 0; j < m_MassPoints.size(); ++j)
		{
			if (m_MassPoints[j]->GetPosition().y > 0)
			{
				t_ApplyGravity = true;
			}
			else
			{
				t_ApplyGravity = false;
				// continue;
			}
		}

		// NOTE: This checks and applies the mass for the objects
		if (t_ApplyGravity == true)
		{
			m_MassPoints[i]->ApplyImpulse(m_MassPoints[i]->GetGravity() * 2 * deltaTime);
		}

		if (m_MassPoints[i]->GetPosition().y < 0)
		{
			m_MassPoints[i]->SetPosition(Vector3(m_MassPoints[i]->GetPosition().x, 0, m_MassPoints[i]->GetPosition().z));
			float t_Dampening = 0.01f;
			m_MassPoints[i]->SetVelocity(Vector3(m_MassPoints[i]->GetVelocity().x, -m_MassPoints[i]->GetVelocity().y * t_Dampening, m_MassPoints[i]->GetVelocity().z));
		}

		m_MassPoints[i]->Update(deltaTime);
	}


	// NOTE: Rod Code
	#pragma region Rod Mass Code

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