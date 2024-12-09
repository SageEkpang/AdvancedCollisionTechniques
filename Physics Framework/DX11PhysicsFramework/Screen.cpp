#include "Screen.h"

Screen::~Screen()
{
	m_GameObjects.clear();
}

void Screen::Update(float deltaTime)
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects) { v->Update(deltaTime); }
	}
}

void Screen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects)
		{
			D3D11_RASTERIZER_DESC cmdesc;
			ID3D11RasterizerState* m_NormalCull;
			ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
			cmdesc.FillMode = D3D11_FILL_SOLID;
			cmdesc.CullMode = D3D11_CULL_NONE;
			cmdesc.FrontCounterClockwise = false;
			device->CreateRasterizerState(&cmdesc, &m_NormalCull);

			pImmediateContext->RSSetState(m_NormalCull);

			// Draw Render Object
			Material t_Material = v->GetRender()->GetMaterial();

			constantBufferData.surface.AmbientMtrl = t_Material.ambient;
			constantBufferData.surface.DiffuseMtrl = t_Material.diffuse;
			constantBufferData.surface.SpecularMtrl = t_Material.specular;

			constantBufferData.World = XMMatrixTranspose(v->GetTransform()->GetWorldMatrix());

			if (v->GetRender()->HasTexture())
			{
				pImmediateContext->PSSetShaderResources(0, 1, v->GetRender()->GetTextureRV());
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

			v->GetRender()->Draw(pImmediateContext);


			// Draw Render Collisions
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

			constantBufferData.World = XMMatrixTranspose(v->GetTransform()->GetWorldMatrix());
			constantBufferData.HasTexture = 0.0f;

			D3D11_MAPPED_SUBRESOURCE t_CollMappedSubresource;
			pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_CollMappedSubresource);
			memcpy(t_CollMappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
			pImmediateContext->Unmap(constBuff, 0);

			v->GetCollider()->Draw(pImmediateContext);
		}
	}
}

void Screen::InsertObjectIntoList(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}
