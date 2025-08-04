#include "Render.h"
#include "GameObjectEntity.h"

Render::Render(Transform * transform)
{
	m_Geometry = Geometry();
	m_Material = Material();
}

Render::Render(Geometry geometry, Material material)
{ 
	m_Geometry.vertexBuffer = nullptr;
}

Render::~Render()
{

}

void Render::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (m_RenderObject == false) return;

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

	if (m_TextureRV != nullptr)
	{
		pImmediateContext->PSSetShaderResources(0, 1, &m_TextureRV);
		constantBufferData.HasTexture = 1.0f;
	}
	else
	{
		constantBufferData.HasTexture = 0.0f;
	}

	D3D11_MAPPED_SUBRESOURCE t_ObjectMappedSubresource;
	pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_ObjectMappedSubresource);
	memcpy(t_ObjectMappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
	pImmediateContext->Unmap(constBuff, 0);

	pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.vertexBuffer, &m_Geometry.vertexBufferStride, &m_Geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(m_Geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

