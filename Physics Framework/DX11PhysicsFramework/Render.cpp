#include "Render.h"

Render::Render()
{
	m_Geometry = Geometry();
	m_Material = Material();
}

Render::Render(Geometry geometry, Material material)
{
	m_Geometry = geometry;
	m_Material = material;
}

Render::~Render()
{
	m_TextureRV = nullptr;
	m_Geometry.indexBuffer = nullptr;
	m_Geometry.vertexBuffer = nullptr;
}

void Render::Draw(ID3D11DeviceContext* pImmediateContext)
{
	if (m_RenderObject == false) return;

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.vertexBuffer, &m_Geometry.vertexBufferStride, &m_Geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(m_Geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(m_Geometry.numberOfIndices, 0, 0);
}

void Render::SetGeometryAndMaterial(char* fileName, Material material, ID3D11Device* device)
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

void Render::SetTexture(const wchar_t* fileName, ID3D11Device* device)
{
	ID3D11ShaderResourceView* t_Texture = nullptr;
	CreateDDSTextureFromFile(device, fileName, nullptr, &t_Texture);
	m_TextureRV = t_Texture;
}
