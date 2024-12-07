#include "GameObject.h"

GameObject::GameObject()
{
	m_TransformComponent = new Transform();
	m_RenderComponent = new Render();
	m_RigidbodyComponent = new RigidbodyObject(m_TransformComponent);
	m_ColliderComponent = new Collider(m_TransformComponent);
	m_Type = Tag();
}

GameObject::GameObject(Tag type)
{
	m_Type = type;
	m_TransformComponent = new Transform();
	m_RenderComponent = new Render();
	m_RigidbodyComponent = new RigidbodyObject(m_TransformComponent);
	m_ColliderComponent = new Collider(m_TransformComponent);
}

GameObject::~GameObject()
{
	delete m_TransformComponent;
	delete m_RenderComponent;
	delete m_RigidbodyComponent;
	delete m_ColliderComponent;
}

void GameObject::Update(float deltaTime)
{
	m_RigidbodyComponent->Update(deltaTime);
	m_TransformComponent->Update(deltaTime);
}


void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	m_RenderComponent->Draw(pImmediateContext);
	m_ColliderComponent->Draw(pImmediateContext);
}

GameObject* GameObject::QuickObject(Vector3 position, Vector3 scale, Vector3 rotation, Collider* collider, char* geoFileName, Material material, const wchar_t* texFileName, ID3D11Device* device)
{
	HRESULT t_HOK = S_OK;

	// Component Inits
	GameObject* t_TempGameObject = new GameObject();
	Render* t_TempRender = new Render();
	Transform* t_TempTransform = new Transform();
	RigidbodyObject* t_TempRigidbody = new RigidbodyObject(t_TempTransform, 1.0f);
	Collider* t_TempCollider = new Collider(t_TempTransform);

	// Transform 
	t_TempGameObject->SetTransform(t_TempTransform);
	t_TempTransform->SetPosition(position);
	t_TempTransform->SetScale(scale);
	t_TempTransform->SetRotation(rotation);

	// Rigidbody
	t_TempGameObject->SetRigidbody(t_TempRigidbody);
	t_TempRigidbody->SetCollider(collider);

	// Collision
	t_TempGameObject->SetCollider(t_TempCollider);

	// Render
	t_TempGameObject->SetRender(t_TempRender);
	t_TempRender->SetGeometryAndMaterial(geoFileName, material, device);
	t_TempRender->SetTexture(texFileName, device);

	return t_TempGameObject;
}
