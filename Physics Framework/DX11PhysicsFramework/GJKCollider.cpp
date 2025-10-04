#include "GJKCollider.h"
#include "GameObjectEntity.h"

GJKCollider::GJKCollider()
{
	m_Vertices.clear();
	m_PositionStore.clear();
}

GJKCollider::~GJKCollider()
{
	m_Vertices.clear();
	m_PositionStore.clear();
}

void GJKCollider::Construct(std::string path, ID3D11Device* device)
{
	std::string t_tempPath = "Resources\\OBJ\\";
	t_tempPath.append(path);
	t_tempPath.append(".obj");

	FillVerticesArray((char*)t_tempPath.c_str());

	Geometry t_Geometry = Geometry();
	MeshData t_Mesh;

	// NOTE: Set the Mesh
	std::string t_tempMeshString = "Resources\\OBJ\\sphere.obj";

	t_Mesh = OBJLoader::Load(t_tempMeshString.data(), device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;
	m_Material = MATERIAL_WIREFRAME;
}

void GJKCollider::Update(float deltaTime)
{
	ColliderEntity::UpdateVertices(m_Owner->m_Transform.m_Scale, m_Owner->m_Transform.m_Position);
}

void GJKCollider::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	for (auto& v : m_PositionStore)
	{
		if (m_RenderCollision == false || m_Geometry.numberOfIndices <= 0) return;

		D3D11_RASTERIZER_DESC cmdesc;
		ID3D11RasterizerState* m_WireCull;
		ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
		cmdesc.FillMode = D3D11_FILL_SOLID;
		cmdesc.CullMode = D3D11_CULL_NONE;
		cmdesc.FrontCounterClockwise = false;
		device->CreateRasterizerState(&cmdesc, &m_WireCull);

		pImmediateContext->RSSetState(m_WireCull);

		constantBufferData.surface.AmbientMtrl = MATERIAL_WIREFRAME.ambient;
		constantBufferData.surface.DiffuseMtrl = MATERIAL_WIREFRAME.diffuse;
		constantBufferData.surface.SpecularMtrl = MATERIAL_WIREFRAME.specular;

		// NOTE: Scale Matrix
		XMMATRIX Scale = XMMatrixScaling(0.1, 0.1, 0.1);

		// NOTE: Orientation Matrix
		XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(m_Owner->m_Transform.m_Orientation.x, m_Owner->m_Transform.m_Orientation.y, m_Owner->m_Transform.m_Orientation.z, m_Owner->m_Transform.m_Orientation.w));

		// NOTE: Position Matrix
		XMMATRIX Position = XMMatrixTranslation(v.x, v.y, v.z);

		XMStoreFloat4x4(m_World, Scale * Orientation * Position);


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
}
