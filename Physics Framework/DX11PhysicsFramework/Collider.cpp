#include "Collider.h"

Collider::Collider(Transform* transform)
{
	m_Transform = transform;
	m_World = new XMFLOAT4X4();

	// Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(transform->GetScale().x, transform->GetScale().y, transform->GetScale().z);

	// Rotation Matrix
	XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(transform->GetOrientation().x, transform->GetOrientation().y, transform->GetOrientation().z, transform->GetOrientation().w));

	// Position Matrix
	XMMATRIX Position = XMMatrixTranslation(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, Scale * Orientation * Position);

	// NOTE: Could / should make these functions static so that for every collision call, you just reference the function
	//Col2 t_ColliderTypes;
	//t_ColliderTypes.first = ColliderType::COLLIDER_BOX;
	//t_ColliderTypes.second = ColliderType::COLLIDER_SPHERE;

	//m_MapColliderFunctions[t_ColliderTypes];

	//CollisionManifold thing;
	//bool Colliding = m_MapColliderFunctions[t_ColliderTypes](this, this, thing);
}

void Collider::Update(float deltaTime)
{
	// Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(m_Transform->GetScale().x, m_Transform->GetScale().y, m_Transform->GetScale().z);

	// Rotation Matrix
	XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(m_Transform->GetOrientation().x, m_Transform->GetOrientation().y, m_Transform->GetOrientation().z, m_Transform->GetOrientation().w));

	// Position Matrix
	XMMATRIX Position = XMMatrixTranslation(m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, Scale * Orientation * Position);
}

void Collider::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
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
	constantBufferData.HasTexture = 0.0f;

	D3D11_MAPPED_SUBRESOURCE t_CollMappedSubresource;
	pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_CollMappedSubresource);
	memcpy(t_CollMappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
	pImmediateContext->Unmap(constBuff, 0);


	pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.vertexBuffer, &m_Geometry.vertexBufferStride, &m_Geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(m_Geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(m_Geometry.numberOfIndices, 0, 0);
}

void Collider::SetCollisionGeometry(char* fileName, Material material, ID3D11Device* device)
{
	Geometry t_Geometry;
	MeshData t_Mesh;

	t_Mesh = OBJLoader::Load(fileName, device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;

	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;
	m_Material = material;
}

// Minkowaski Difference Function
Vector3 Collider::FindFurthestPoint(Vector3 direction)
{
	// STEP 1: Find the Max Point
	Vector3 t_MaxPoint;
	float t_MaxDistance = -FLT_MAX;

	// NOTE: Clear the Vertices to insert new position points
	m_Vertices.clear();

	// NOTE: Update Vertices Positions
	for (int i = 0; i < m_PositionStore.size(); ++i)
	{
		Vector3 t_VecPos = (m_PositionStore[i] * m_Transform->GetScale()) + m_Transform->GetPosition();
		m_Vertices.push_back(t_VecPos);
	}

	if (!m_Vertices.empty())
	{
		// NOTE: Find furthest vertex
		for (Vector3& v : m_Vertices)
		{
			float t_Distance = Vector::CalculateDotProductNotNorm(v, direction); // NOTE: May have to change dot product back to normalise one

			if (t_Distance > t_MaxDistance)
			{
				t_MaxDistance = t_Distance;
				t_MaxPoint = v;
			}
		}
	}

	return t_MaxPoint;
}

Vector3 Collider::SphereNearestPoint(Vector3 point)
{
	Vector3 t_SphereToPoint = Vector::Normalise(point - GetPosition());
	t_SphereToPoint *= m_Radius;
	return t_SphereToPoint + GetPosition();
}

void Collider::FillVerticesArray(char* path, Transform* objectTransform)
{
	// NOTE: Fill array with the different mesh load values
	m_PositionStore = MeshLoader::LoadObj(path);
}
