#include "ColliderEntity.h"
#include "GameObjectEntity.h"

ColliderEntity::ColliderEntity() : m_HasCollided(false), m_IsActivated(true), m_IsTrigger(false)
{
	m_World = new XMFLOAT4X4();
	m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
	m_ObjectList.clear();
}

ColliderEntity::~ColliderEntity()
{
	delete m_World;
	if (!m_ObjectList.empty()) { m_ObjectList.clear(); }

	m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
}

void ColliderEntity::TriggerQuery(GameObjectEntity* gameObject)
{
	if (m_IsActivated == false) { return; }

	if (m_Quered == false)
	{
		m_Quered = true;

		// NOTE: Game Object has entered trigger
		if (m_ObjectList.find(gameObject) == m_ObjectList.end() && gameObject->FindChildComponent<ColliderEntity>()->m_HasCollided == true)
		{
			m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_ENTERED;
			m_ObjectList.insert(gameObject);
			return;
		}

		// NOTE: Check if the Object List is there
		if (m_ObjectList.empty()) { return; }

		// NOTE: Game Object has stayed in the trigger
		if (m_ObjectList.find(gameObject) != m_ObjectList.end() && gameObject->FindChildComponent<ColliderEntity>()->m_HasCollided == true)
		{
			m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_STAYED;
			return;
		}

		// NOTE: Game Object has exited the trigger
		if (m_ObjectList.find(gameObject) != m_ObjectList.end() && gameObject->FindChildComponent<ColliderEntity>()->m_HasCollided == false)
		{
			m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_EXITED;
			m_ObjectList.erase(gameObject);
			return;
		}

	}
}

void ColliderEntity::TriggerEnteredExecute(std::function<void()> func)
{
	m_TriggerEnteredLambda = func;
}

void ColliderEntity::TriggerStayedExecute(std::function<void()> func)
{
	m_TriggerStayedLambda = func;
}

void ColliderEntity::TriggerExitedExecute(std::function<void()> func)
{
	m_TriggerExitedLambda = func;
}

void ColliderEntity::TriggerQueryExecute()
{
	m_Quered = false;
	switch (m_TriggerState)
	{
	case TriggerAreaState::TRIGGER_AREA_STATE_ENTERED:
		if (m_TriggerEnteredLambda != nullptr)
		{
			m_TriggerEnteredLambda();
		}
		m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
		break;

	case TriggerAreaState::TRIGGER_AREA_STATE_STAYED:
		if (m_TriggerStayedLambda != nullptr)
		{
			m_TriggerStayedLambda();
		}
		m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
		break;

	case TriggerAreaState::TRIGGER_AREA_STATE_EXITED:
		if (m_TriggerExitedLambda != nullptr)
		{
			m_TriggerExitedLambda();
		}
		m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
		break;

	case TriggerAreaState::TRIGGER_AREA_STATE_NONE:
		m_TriggerState = TriggerAreaState::TRIGGER_AREA_STATE_NONE;
		break;

	default:
		break;
	}
}

void ColliderEntity::Update(float deltaTime)
{
	// NOTE: Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(m_Owner->m_Transform.m_Scale.width, m_Owner->m_Transform.m_Scale.height, m_Owner->m_Transform.m_Scale.length);

	// NOTE: Orientation Matrix
	XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(m_Owner->m_Transform.m_Orientation.x, m_Owner->m_Transform.m_Orientation.y, m_Owner->m_Transform.m_Orientation.z, m_Owner->m_Transform.m_Orientation.w));

	// NOTE: Position Matrix
	XMMATRIX Position = XMMatrixTranslation(m_Owner->m_Transform.m_Position.x, m_Owner->m_Transform.m_Position.y, m_Owner->m_Transform.m_Position.z);

	XMStoreFloat4x4(m_World, Scale * Orientation * Position);
}

void ColliderEntity::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (m_RenderCollision == false || m_Geometry.numberOfIndices <= 0) return;

	D3D11_RASTERIZER_DESC cmdesc;
	ID3D11RasterizerState* m_WireCull;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_WIREFRAME;
	cmdesc.CullMode = D3D11_CULL_NONE;
	cmdesc.FrontCounterClockwise = false;
	device->CreateRasterizerState(&cmdesc, &m_WireCull);

	pImmediateContext->RSSetState(m_WireCull);

	constantBufferData.surface.AmbientMtrl = MATERIAL_WIREFRAME.ambient;
	constantBufferData.surface.DiffuseMtrl = MATERIAL_WIREFRAME.diffuse;
	constantBufferData.surface.SpecularMtrl = MATERIAL_WIREFRAME.specular;

	XMMATRIX temp = XMLoadFloat4x4(m_World);
	constantBufferData.World = XMMatrixTranspose(temp);

	D3D11_MAPPED_SUBRESOURCE t_CollMappedSubresource;
	pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_CollMappedSubresource);
	memcpy(t_CollMappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
	pImmediateContext->Unmap(constBuff, 0);

	pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.vertexBuffer, &m_Geometry.vertexBufferStride, &m_Geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(m_Geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(m_Geometry.numberOfIndices, 0, 0);
}

void ColliderEntity::SetCollisionGeometry(char* fileName, Material material, ID3D11Device* device)
{
	Geometry t_Geometry{};
	MeshData t_Mesh{};

	t_Mesh = OBJLoader::Load(fileName, device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;

	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;

	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;
	m_Material = material;
}

//void Collider::FillVerticesArray(char* path, Transform* objectTransform)
//{
//	// NOTE: Fill array with the different mesh load values
//	std::vector<Vector3> t_TempVec = MeshLoader::LoadObj(path);
//
//	for (int i = 0; i < t_TempVec.size(); ++i)
//	{
//		Vector3 t_VecPos = (t_TempVec[i] * objectTransform->GetScale()) + objectTransform->GetPosition();
//		m_Vertices.push_back(t_VecPos);
//	}
//}
