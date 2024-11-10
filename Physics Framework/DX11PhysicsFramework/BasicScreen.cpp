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
	ID3D11ShaderResourceView* _StoneTextureRV = nullptr;
	CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &_StoneTextureRV);

	herculesGeometry.indexBuffer = _objMeshData.IndexBuffer;
	herculesGeometry.numberOfIndices = _objMeshData.IndexCount;
	herculesGeometry.vertexBuffer = _objMeshData.VertexBuffer;
	herculesGeometry.vertexBufferOffset = _objMeshData.VBOffset;
	herculesGeometry.vertexBufferStride = _objMeshData.VBStride;

	Material shinyMaterial;
	shinyMaterial.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	GameObject* t_DonutObject = new GameObject(Tag("Donut", PhysicTag::PHYSICS_STATIC));
	Render* t_DonutRender = new Render();
	Transform* t_DonutTransform = new Transform();
	RigidbodyObject* t_DonutRigidBody = new RigidbodyObject(t_DonutTransform, 5.0f);
	SphereCollider* t_DonutCollider = new SphereCollider(t_DonutTransform, 5.0f);

	t_DonutObject->SetTransform(t_DonutTransform);
	t_DonutTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_DonutTransform->SetPosition(-5.0f, 0.5f, 10.0f);

	t_DonutObject->SetRigidbody(t_DonutRigidBody);
	t_DonutRigidBody->SetCollider(t_DonutCollider);

	t_DonutObject->SetRender(t_DonutRender);
	t_DonutRender->SetGeometry(herculesGeometry);
	t_DonutRender->SetMaterial(shinyMaterial);
	t_DonutRender->SetTextureRV(_StoneTextureRV);

	m_Objects.push_back(t_DonutObject);
}

BasicScreen::~BasicScreen()
{
	if (!m_Objects.empty())
	{
		m_Objects.clear();
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
	if (!m_Objects.empty())
	{
		for (auto& v : m_Objects)
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
	}
}
