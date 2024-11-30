#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	// May need to add camera to this
	m_ScreenName = screenName;

	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;
	m_ScreenInformation.screenState = ScreenState::SCREEN_CURRENT;
	
	// Donut Object
	GameObject* t_DonutObject = new GameObject(Tag("Donut", PhysicTag::PHYSICS_STATIC));
	Render* t_DonutRender = new Render();
	Transform* t_DonutTransform = new Transform();

	RigidbodyObject* t_DonutRigidBody = new RigidbodyObject(t_DonutTransform, 1.0f);
	SphereCollider* t_DonutCollider = new SphereCollider(t_DonutTransform, 5.0f);

	t_DonutObject->SetTransform(t_DonutTransform);
	t_DonutTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_DonutTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_DonutTransform->SetPosition(-5.0f, 10.0f, 10.0f);

	t_DonutObject->SetRigidbody(t_DonutRigidBody);
	t_DonutRigidBody->SetCollider(t_DonutCollider);

	t_DonutObject->SetRender(t_DonutRender);

	Geometry t_DonutGeometry;
	MeshData t_DonutMesh;

	t_DonutMesh = OBJLoader::Load("Resources\\OBJ\\donut.obj", device);
	t_DonutGeometry.indexBuffer = t_DonutMesh.IndexBuffer;
	t_DonutGeometry.numberOfIndices = t_DonutMesh.IndexCount;
	t_DonutGeometry.vertexBuffer = t_DonutMesh.VertexBuffer;
	t_DonutGeometry.vertexBufferOffset = t_DonutMesh.VBOffset;
	t_DonutGeometry.vertexBufferStride = t_DonutMesh.VBStride;

	t_DonutRender->SetGeometry(t_DonutGeometry);
	t_DonutRender->SetMaterial(MATERIAL_SHINY);

	// Texture Data
	ID3D11ShaderResourceView* t_DonutTexture = nullptr;
	CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_DonutTexture);

	t_DonutRender->SetTextureRV(t_DonutTexture);

	m_Objects.push_back(t_DonutObject);


	// Plane Object
	GameObject* t_PlaneObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_STATIC));
	Render* t_PlaneRender = new Render();
	Transform* t_PlaneTransform = new Transform();
	RigidbodyObject* t_PlaneRigidbody = new RigidbodyObject(t_PlaneTransform, 0.0f);
	PlaneCollider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform);

	t_PlaneObject->SetTransform(t_PlaneTransform);
	t_PlaneTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_PlaneTransform->SetPosition(0.0f, 0.0f, 10.0f);

	t_PlaneObject->SetRigidbody(t_PlaneRigidbody);
	t_PlaneRigidbody->SetCollider(t_PlaneCollider);

	t_PlaneObject->SetRender(t_PlaneRender);

	// Mesh Data
	Geometry t_PlaneGeometry;
	MeshData t_PlaneMesh;

	t_PlaneMesh = OBJLoader::Load("Resources\\OBJ\\plane.obj", device);
	t_PlaneGeometry.indexBuffer = t_PlaneMesh.IndexBuffer;
	t_PlaneGeometry.numberOfIndices = t_PlaneMesh.IndexCount;
	t_PlaneGeometry.vertexBuffer = t_PlaneMesh.VertexBuffer;
	t_PlaneGeometry.vertexBufferOffset = t_PlaneMesh.VBOffset;
	t_PlaneGeometry.vertexBufferStride = t_PlaneMesh.VBStride;

	t_PlaneRender->SetGeometry(t_PlaneGeometry);
	t_PlaneRender->SetMaterial(MATERIAL_SHINY);

	// Texture Data
	ID3D11ShaderResourceView* t_PlaneTexture = nullptr;
	CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_PlaneTexture);

	t_PlaneRender->SetTextureRV(t_PlaneTexture);

	m_Objects.push_back(t_PlaneObject);
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
