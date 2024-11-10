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
	// We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.vertexBuffer, &m_Geometry.vertexBufferStride, &m_Geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(m_Geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(m_Geometry.numberOfIndices, 0, 0);
}
