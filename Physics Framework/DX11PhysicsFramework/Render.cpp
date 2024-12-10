#include "Render.h"

Render::Render(Transform* transform)
{
	m_Geometry = Geometry();
	m_Material = Material();
	m_World = new XMFLOAT4X4();

	m_Transform = transform;

	// Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(transform->GetScale().x, transform->GetScale().y, transform->GetScale().z);

	// Rotation Matrix
	XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(transform->GetOrientation().x, transform->GetOrientation().y, transform->GetOrientation().z, transform->GetOrientation().w));

	// Position Matrix
	XMMATRIX Position = XMMatrixTranslation(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, Scale * Orientation * Position);
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

void Render::Update(float deltaTime)
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

	XMMATRIX temp = XMLoadFloat4x4(m_World);
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
