#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	// May need to add camera to this
	m_ScreenName = screenName;

	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;
	m_ScreenInformation.screenState = ScreenState::SCREEN_CURRENT;

	Geometry herculesGeometry;
	MeshData _objMeshData;
	_objMeshData = OBJLoader::Load("Resources\\OBJ\\donut.obj", device);

	herculesGeometry.indexBuffer = _objMeshData.IndexBuffer;
	herculesGeometry.numberOfIndices = _objMeshData.IndexCount;
	herculesGeometry.vertexBuffer = _objMeshData.VertexBuffer;
	herculesGeometry.vertexBufferOffset = _objMeshData.VBOffset;
	herculesGeometry.vertexBufferStride = _objMeshData.VBStride;

	Material shinyMaterial;
	shinyMaterial.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	GameObject* t_GameObject = new GameObject("Donut", herculesGeometry, shinyMaterial);
	ID3D11ShaderResourceView* _StoneTextureRV = nullptr;
	// CreateDDSTextureFromFile(device, L"Resources\\Textures\\Hercules_COLOR.dds", nullptr, &_StoneTextureRV);

	t_GameObject->SetScale(1.0f, 1.0f, 1.0f);
	t_GameObject->SetPosition(-5.0f, 0.5f, 10.0f);
	t_GameObject->SetRotation(0, 0, 0);
	// t_GameObject->SetTextureRV(_StoneTextureRV);

	m_Objects.push_back(t_GameObject);

	delete t_GameObject;
	t_GameObject = nullptr;
}

BasicScreen::~BasicScreen()
{
	if (!m_Objects.empty())
	{

	}
}

void BasicScreen::Update(Camera* camera, float deltaTime)
{
	if (!m_Objects.empty())
	{
		for (auto& v : m_Objects)
		{
			v->Update(deltaTime);
		}
	}
}

void BasicScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext)
{
	//if (!m_Objects.empty())
	//{
	//	for (auto& v : m_Objects)
	//	{
	//		Material t_Material = v->GetMaterial();

	//		constantBufferData.surface.AmbientMtrl = XMFLOAT4(0.1, 0.1, 0.1, 0.1);
	//		constantBufferData.surface.DiffuseMtrl = XMFLOAT4(0.1, 0.1, 0.1, 0.1);
	//		constantBufferData.surface.SpecularMtrl = XMFLOAT4(0.1, 0.1, 0.1, 0.1);

	//		constantBufferData.World = XMMatrixTranspose(v->GetWorldMatrix());

	//		if (v->HasTexture())
	//		{
	//			pImmediateContext->PSSetShaderResources(0, 1, v->GetTextureRV());
	//			constantBufferData.HasTexture = 1.0f;
	//		}
	//		else
	//		{
	//			constantBufferData.HasTexture = 0.0f;
	//		}

	//		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	//		pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	//		memcpy(mappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
	//		pImmediateContext->Unmap(constBuff, 0);

	//		v->Draw(pImmediateContext);
	//	}
	//}
}
