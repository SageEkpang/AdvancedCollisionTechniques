#include "Screen.h"

Screen::~Screen()
{
	if (!m_GameObjects.empty()) { m_GameObjects.clear(); }
}

void Screen::Update(float deltaTime)
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects) { v->Update(deltaTime); }
	}
}

void Screen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext)
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects)
		{
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

			D3D11_MAPPED_SUBRESOURCE mappedSubresource;
			pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
			memcpy(mappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
			pImmediateContext->Unmap(constBuff, 0);

			v->Draw(pImmediateContext);
		}

		for (auto& c : m_ColliderObjects)
		{


			D3D11_MAPPED_SUBRESOURCE mappedSubresource;
			pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
			memcpy(mappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
			pImmediateContext->Unmap(constBuff, 0);

			// v->Draw(pImmediateContext);
		}
	}
}

void Screen::InsertObjectIntoList(GameObject* gameObject)
{
	// Insert the Game Objects and Colliders
	m_GameObjects.push_back(gameObject);
	m_ColliderObjects.push_back(gameObject->GetRigidbody()->GetCollider());
}
