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
	for (auto& v : m_MassPoints) { v->Update(deltaTime); }

	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		for (int j = 0; j < m_MassPoints.size(); ++j)
		{
			if (i == j) { continue; }

			// NOTE: Rod / Spring Code
					
			// NOTE: "Current Length" is just the distance between the two vectors magnitude
			float t_CurrentLength = Vector3::S_Magnitude(m_MassPoints[i]->m_Transform.m_Position - m_MassPoints[j]->m_Transform.m_Position) / 2;
					
			// NOTE: Skip Current Iteration
			if (t_CurrentLength == m_TargetDistances[i][j]) { continue; }
				
			// NOTE: Normal Calculation
			Vector3 t_Normal = m_MassPoints[i]->m_Transform.m_Position - m_MassPoints[j]->m_Transform.m_Position;
					
			float t_Target = m_TargetDistances[i][j]; // NOTE: This is the "distance" that the rods need to be at
			Vector3 t_Disperse = m_MassPoints[i]->m_Transform.m_Position - m_MassPoints[j]->m_Transform.m_Position;
			float t_Distance = t_CurrentLength;
		
			Vector3 t_NewNormal = t_Disperse / t_Distance;
			float t_Delta = t_Target - t_Distance;
		
			Vector3 t_TargetPosA = m_MassPoints[i]->m_Transform.m_Position + t_Delta * t_NewNormal.Normalise();
			Vector3 t_TargetPosB = m_MassPoints[j]->m_Transform.m_Position - t_Delta * t_NewNormal.Normalise();
		
			m_MassPoints[i]->m_Transform.m_Position = t_TargetPosA;
			m_MassPoints[j]->m_Transform.m_Position = t_TargetPosB;
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
		t_tempGameObject->AddComponent<Rigidbody3DObject>()->Construct(1, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		m_MassPoints.push_back(t_tempGameObject);
	}
}
