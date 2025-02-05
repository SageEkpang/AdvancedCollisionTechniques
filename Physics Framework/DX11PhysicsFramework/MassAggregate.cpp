#include "MassAggregate.h"

MassAggregate::MassAggregate(char* filePath, Vector3 position, float mass, int size, ID3D11Device* device)
{
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

		// NOTE: Update Mass Points with Gravity
		v->AddForce(v->GetGravity() * v->GetMass());
		v->Update(deltaTime);
	}

	// NOTE: Rod Code
	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		for (int j = 0; j < m_MassPoints.size(); ++j)
		{
			if (i == j) { continue; }
			
			// NOTE: "Current Length" is just the distance between the two vectors magnitude
			// NOTE: Could also be the two vectors take away from each other
			float t_CurrentLength = Vector::Magnitude(m_MassPoints[j]->GetPosition() - m_MassPoints[i]->GetPosition());

			if (t_CurrentLength == m_Size) { continue; }

			CollisionManifold t_ColManifold;

			// NOTE: 
			Vector3 t_Normal = m_MassPoints[j]->GetPosition() - m_MassPoints[i]->GetPosition();
			t_Normal = t_Normal.Normalise();

			if (t_CurrentLength > m_Size)
			{
				t_ColManifold.collisionNormal = t_Normal;
				t_ColManifold.penetrationDepth = t_CurrentLength - m_Size;
			}
			else
			{
				t_ColManifold.collisionNormal = t_Normal * -1;
				t_ColManifold.penetrationDepth = m_Size - t_CurrentLength;
			}

			// TODO: Restitution is 0

		}
	}



}

void MassAggregate::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	for (auto& v : m_MassPoints)
	{
		v->Draw(constantBufferData, constBuff, pImmediateContext, device);
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