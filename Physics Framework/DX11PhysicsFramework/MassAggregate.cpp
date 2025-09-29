#include "MassAggregate.h"
#include "GameObjectEntity.h"
#include "SphereCollider.h"

MassAggregate::MassAggregate()
{
	m_Vertices.clear();
	m_MassPoints.clear();
}

MassAggregate::~MassAggregate()
{
	for (int i = 0; i < m_MassPoints.size(); ++i) { delete[] m_TargetDistances[i]; }
	delete[] m_TargetDistances;

	m_Vertices.clear();
	m_MassPoints.clear();
}

void MassAggregate::Construct(std::string path, ID3D11Device* device)
{
	std::string t_tempPath = "Resources\\OBJ\\";
	t_tempPath.append(path);
	t_tempPath.append(".obj");

	FillVerticesArray((char*)t_tempPath.c_str(), device);

	Geometry t_Geometry = Geometry();
	MeshData t_Mesh;


	// NOTE: Making Array
	m_TargetDistances = new float* [m_MassPoints.size()];
	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		m_TargetDistances[i] = new float[m_MassPoints.size()];
	}

	// NOTE: File Target Positions
	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		for (int j = 0; j < m_MassPoints.size(); ++j)
		{
			if (i == j) { continue; }

			// NOTE: Store Target distances to other points
			float t_CurrentLength = Vector3::S_Magnitude(m_MassPoints[i]->m_Transform.m_Position - m_MassPoints[j]->m_Transform.m_Position) / 2;
			m_TargetDistances[i][j] = t_CurrentLength;
		}
	}

	int i = 9;
}

void MassAggregate::Update(float deltaTime)
{
	// NOTE: Update all the points with the Rod Code
	
	// NOTE: Spring Code : Hooks Law (F = -kx)
	// F = Force
	// k = Spring Constant
	// x = difference between current length and resting length

	// Spring Dampening (Fd = -vb)
	// Fd = Resultant dampening force
	// v = relative velocity between two particles ( 0 to 1)
	// b = dampening force

	// Result: F = (-kx) + (-vb)

	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		for (int j = 0; j < m_MassPoints.size(); ++j)
		{
			if (i == j) { continue; }

			Vector3 t_RelativePosition = m_MassPoints[i]->m_Transform.m_Position - m_MassPoints[j]->m_Transform.m_Position;
			Vector3 t_RelativeVelocity = m_MassPoints[i]->GetComponent<Rigidbody3DObject>()->GetVelocity() - m_MassPoints[j]->GetComponent<Rigidbody3DObject>()->GetVelocity();
					
			float t_X = (Vector3::S_Magnitude(t_RelativePosition) * 0.5f) - m_TargetDistances[i][j];
			float t_V = Vector3::S_Magnitude(t_RelativeVelocity);

			float t_K = -50.0f; // [ -n to 0 ]
			float t_F = (-t_K * t_X); // +(-t_B * t_V);

			Vector3 t_Impulse = (Vector3::S_Normalise(t_RelativePosition) * 0.5) * t_F;

			float t_B = 0.1f; // [ 0 to 1 ]
			Vector3 t_DampeningForce = t_RelativeVelocity * t_B;

			m_MassPoints[i]->GetComponent<Rigidbody3DObject>()->ApplyImpulse((t_Impulse * m_MassPoints[i]->GetComponent<Rigidbody3DObject>()->m_Mass) * -1.f * m_MassPoints[i]->GetComponent<Rigidbody3DObject>()->GetInverseMass());
			m_MassPoints[i]->GetComponent<Rigidbody3DObject>()->ApplyImpulse(t_DampeningForce * -1.f);

			m_MassPoints[j]->GetComponent<Rigidbody3DObject>()->ApplyImpulse((t_Impulse * m_MassPoints[j]->GetComponent<Rigidbody3DObject>()->m_Mass) * m_MassPoints[j]->GetComponent<Rigidbody3DObject>()->GetInverseMass());
			m_MassPoints[j]->GetComponent<Rigidbody3DObject>()->ApplyImpulse(t_DampeningForce);

		}
	}

	for (auto& v : m_MassPoints) { v->Update(deltaTime); }
}

void MassAggregate::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	for (auto& v : m_MassPoints)
	{
		v->Draw(constantBufferData, constBuff, pImmediateContext, device);
	}
}

void MassAggregate::FillVerticesArray(char* path, ID3D11Device* device)
{
	// NOTE: Fill array with the different mesh load values
	std::vector<Vector3> t_TempVec = MeshLoader::LoadObj(path);

	for (int i = 0; i < t_TempVec.size(); ++i)
	{
		// NOTE: Store Untransformed Vertices
		m_Vertices.push_back(t_TempVec[i]);

		// NOTE: Store Transformed Vertices
		Vector3 t_VecPos = (t_TempVec[i] * m_Owner->m_Transform.m_Scale) + m_Owner->m_Transform.m_Position;

		GameObjectEntity* t_tempGameObject = new GameObjectEntity();
		t_tempGameObject->m_Transform.m_Position = t_VecPos;
		t_tempGameObject->m_Transform.m_Scale = Vector3(1, 1, 1);
		t_tempGameObject->AddComponent<Mesh>()->Construct("sphere", device);
		t_tempGameObject->AddComponent<SphereCollider>()->Construct(1, device);
		t_tempGameObject->AddComponent<Rigidbody3DObject>()->Construct(10, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		m_MassPoints.push_back(t_tempGameObject);
	}
}
