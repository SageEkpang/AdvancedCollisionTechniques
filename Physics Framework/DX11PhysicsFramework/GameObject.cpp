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
	m_TransformComponent->Update(deltaTime);
	m_RigidbodyComponent->Update(deltaTime);
}


void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	m_RenderComponent->Draw(pImmediateContext);
}
