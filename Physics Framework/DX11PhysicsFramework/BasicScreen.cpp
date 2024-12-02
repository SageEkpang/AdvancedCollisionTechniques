#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	// May need to add camera to this
	m_ScreenName = screenName;

	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;
	m_ScreenInformation.screenState = ScreenState::SCREEN_CURRENT;

	#pragma region Donut Object

	// Donut Object
	GameObject* t_DonutObject = new GameObject(Tag("Donut", PhysicTag::PHYSICS_STATIC));
	Render* t_DonutRender = new Render();
	Transform* t_DonutTransform = new Transform();

	RigidbodyObject* t_DonutRigidBody = new RigidbodyObject(t_DonutTransform, 0.0f);
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

	#pragma endregion

	#pragma region Plane Object

	// Plane Object
	GameObject* t_PlaneObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_STATIC));
	Render* t_PlaneRender = new Render();
	Transform* t_PlaneTransform = new Transform();
	RigidbodyObject* t_PlaneRigidbody = new RigidbodyObject(t_PlaneTransform, 0.0f);
	PlaneCollider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform);

	t_PlaneObject->SetTransform(t_PlaneTransform);
	t_PlaneTransform->SetScale(5.0f, 1.0f, 5.0f);
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

	#pragma endregion

	#pragma region Head Object

	// Head Object
	GameObject* t_HeadObject = new GameObject(Tag("Head", PhysicTag::PHYSICS_STATIC));
	Render* t_HeadRender = new Render();
	Transform* t_HeadTransform = new Transform();
	RigidbodyObject* t_HeadRigidbody = new RigidbodyObject(t_HeadTransform, 0.0f);
	PlaneCollider* t_HeadCollider = new PlaneCollider(t_HeadTransform);

	t_HeadObject->SetTransform(t_HeadTransform);
	t_HeadTransform->SetScale(0.2f, 0.2f, 0.2f);
	t_HeadTransform->SetRotation(0.0f, 180.0f, 0.0f);
	t_HeadTransform->SetPosition(5.0f, 5.0f, 10.0f);

	t_HeadObject->SetRigidbody(t_HeadRigidbody);
	t_HeadRigidbody->SetCollider(t_HeadCollider);

	t_HeadObject->SetRender(t_HeadRender);

	// Mesh Data
	Geometry t_HeadGeometry;
	MeshData t_HeadMesh;

	t_HeadMesh = OBJLoader::Load("Resources\\OBJ\\joelModel.obj", device);
	t_HeadGeometry.indexBuffer = t_HeadMesh.IndexBuffer;
	t_HeadGeometry.numberOfIndices = t_HeadMesh.IndexCount;
	t_HeadGeometry.vertexBuffer = t_HeadMesh.VertexBuffer;
	t_HeadGeometry.vertexBufferOffset = t_HeadMesh.VBOffset;
	t_HeadGeometry.vertexBufferStride = t_HeadMesh.VBStride;

	t_HeadRender->SetGeometry(t_HeadGeometry);
	t_HeadRender->SetMaterial(MATERIAL_SHINY);

	// Texture Data
	ID3D11ShaderResourceView* t_HeadTexture = nullptr;
	CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_HeadTexture);

	t_HeadRender->SetTextureRV(t_HeadTexture);

	m_Objects.push_back(t_HeadObject);

	#pragma endregion

	// Spike Object
	GameObject* t_SpikeObject = new GameObject(Tag("Spike", PhysicTag::PHYSICS_STATIC));
	Render* t_SpikeRender = new Render();
	Transform* t_SpikeTransform = new Transform();
	RigidbodyObject* t_SpikeRigidbody = new RigidbodyObject(t_HeadTransform, 0.0f);
	PlaneCollider* t_SpikeCollider = new PlaneCollider(t_HeadTransform);

	t_SpikeObject->SetTransform(t_SpikeTransform);
	t_SpikeTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_SpikeTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_SpikeTransform->SetPosition(15.0f, 5.0f, 10.0f);

	t_SpikeObject->SetRigidbody(t_SpikeRigidbody);
	t_SpikeRigidbody->SetCollider(t_SpikeCollider);

	t_SpikeObject->SetRender(t_SpikeRender);

	// Mesh Data
	Geometry t_SpikeGeometry;
	MeshData t_SpikeMesh;

	t_SpikeMesh = OBJLoader::Load("Resources\\OBJ\\SpikeBall.obj", device);
	t_SpikeGeometry.indexBuffer = t_SpikeMesh.IndexBuffer;
	t_SpikeGeometry.numberOfIndices = t_SpikeMesh.IndexCount;
	t_SpikeGeometry.vertexBuffer = t_SpikeMesh.VertexBuffer;
	t_SpikeGeometry.vertexBufferOffset = t_SpikeMesh.VBOffset;
	t_SpikeGeometry.vertexBufferStride = t_SpikeMesh.VBStride;

	t_SpikeRender->SetGeometry(t_SpikeGeometry);
	t_SpikeRender->SetMaterial(MATERIAL_SHINY);

	// Texture Data
	ID3D11ShaderResourceView* t_SpikeTexture = nullptr;
	CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_SpikeTexture);

	t_SpikeRender->SetTextureRV(t_SpikeTexture);

	m_Objects.push_back(t_SpikeObject);





	// Test Object
	// HRESULT t_HOK = S_OK;

	// GameObject* t_TestObject = new GameObject(Tag("Test", PhysicTag::PHYSICS_STATIC));
	// SphereCollider* t_TestCollider = new SphereCollider(t_TestObject->GetTransform(), 10);
	// t_TestObject->QuickObject(Vector3(0, 10, 10), Vector3(1, 1, 1), Vector3(0, 180, 0), NULL, "Resources\\OBJ\\joelModel.obj", MATERIAL_SHINY, L"Resources\\Textures\\stone.dds", device);
	
	// if (FAILED(t_HOK)) { std::cerr << "Object Was not constructed Properly" << std::endl; }
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
