#include "Mesh.h"
#include "GameObjectEntity.h"

void Mesh::Construct(char* fileName, ID3D11Device* device)
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
	m_Material = MATERIAL_GROUND;
}

void Mesh::Construct(char* fileName, Material material, Geometry geometry, ID3D11Device* device)
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

Mesh::Mesh()
{
	m_Material = Material();
	m_Geometry = Geometry();
	m_Geometry.vertexBuffer = nullptr;
	m_Geometry.indexBuffer = nullptr;
}

Mesh::~Mesh()
{
	m_Material = Material();
	m_Geometry = Geometry();
	m_Geometry.vertexBuffer = nullptr;
	m_Geometry.indexBuffer = nullptr;
}

void Mesh::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (m_RenderMesh == false) { return; }

	D3D11_RASTERIZER_DESC cmdesc;
	ID3D11RasterizerState* m_NormalCull;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;
	cmdesc.FrontCounterClockwise = false;
	device->CreateRasterizerState(&cmdesc, &m_NormalCull);

	pImmediateContext->RSSetState(m_NormalCull);

	// Draw Render Object
	constantBufferData.surface.AmbientMtrl = m_Material.ambient;
	constantBufferData.surface.DiffuseMtrl = m_Material.diffuse;
	constantBufferData.surface.SpecularMtrl = m_Material.specular;

	XMMATRIX temp = XMLoadFloat4x4(m_Owner->m_Transform.m_World);
	constantBufferData.World = XMMatrixTranspose(temp);


	D3D11_MAPPED_SUBRESOURCE t_ObjectMappedSubresource;
	pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_ObjectMappedSubresource);
	memcpy(t_ObjectMappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
	pImmediateContext->Unmap(constBuff, 0);

	pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.vertexBuffer, &m_Geometry.vertexBufferStride, &m_Geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(m_Geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

void Mesh::SetGeometryAndMaterial(char* fileName, Material material, ID3D11Device* device)
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

