#include "GameObject.h"

GameObject::GameObject(Tag type)
{
	m_Type = type;
	m_TransformComponent = new Transform();
	m_RenderComponent = new Render();
	m_RigidbodyComponent = new RigidbodyObject(m_TransformComponent);
}

GameObject::~GameObject()
{
	delete m_TransformComponent;
	delete m_RenderComponent;
	delete m_RigidbodyComponent;
}

void GameObject::Update(float deltaTime)
{
	m_RigidbodyComponent->Update(deltaTime);
	m_TransformComponent->Update(deltaTime);
}


void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	m_RenderComponent->Draw(pImmediateContext);
}

HRESULT GameObject::QuickObject(Vector3 position, Vector3 scale, Vector3 rotation, Collider* collider, char* geoFileName, Material material, const wchar_t* texFileName, ID3D11Device* device)
{
	HRESULT t_HOK = S_OK;

	Render* t_TempRender = new Render();
	Transform* t_TempTransform = new Transform();
	RigidbodyObject* t_TempRigidbody = new RigidbodyObject(t_TempTransform, 1.0f);

	SetTransform(t_TempTransform);
	t_TempTransform->SetPosition(position);
	t_TempTransform->SetScale(scale);
	t_TempTransform->SetRotation(rotation);

	// if (m_TransformComponent == nullptr) { return E_FAIL; }

	SetRigidbody(t_TempRigidbody);
	t_TempRigidbody->SetCollider(collider);

	// if (m_RigidbodyComponent == nullptr) { return E_FAIL; }

	SetRender(t_TempRender);
	// if (m_RenderComponent == nullptr) { return E_FAIL; }

	// Geometry and Mesh Setting
	Geometry t_TempGeometry;
	MeshData t_TempMeshData;

	t_TempMeshData = OBJLoader::Load("Resources\\OBJ\\joelModel.obj", device);
	t_TempGeometry.indexBuffer = t_TempMeshData.IndexBuffer;
	t_TempGeometry.numberOfIndices = t_TempMeshData.IndexCount;
	t_TempGeometry.vertexBuffer = t_TempMeshData.VertexBuffer;
	t_TempGeometry.vertexBufferOffset = t_TempMeshData.VBOffset;
	t_TempGeometry.vertexBufferStride = t_TempMeshData.VBStride;

	t_TempRender->SetGeometry(t_TempGeometry);
	t_TempRender->SetMaterial(material);

	// Texture Setting
	ID3D11ShaderResourceView* t_TempTexture = nullptr;
	CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_TempTexture);

	t_TempRender->SetTextureRV(t_TempTexture);

	return S_OK;
}
