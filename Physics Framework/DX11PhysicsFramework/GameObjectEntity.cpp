#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{

}

GameObjectEntity::~GameObjectEntity()
{
	
}

void GameObjectEntity::Update(float deltaTime)
{
	/*m_RigidbodyComponent->Update(deltaTime);
	m_TransformComponent->Update(deltaTime);
	m_RenderComponent->Update(deltaTime);
	m_ColliderComponent->Update(deltaTime);*/
}


void GameObjectEntity::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	//if (m_RenderComponent != nullptr)
	//{
	//	m_RenderComponent->Draw(constantBufferData, constBuff, pImmediateContext, device);
	//}

	//if (m_ColliderComponent != nullptr)
	//{
	//	m_ColliderComponent->Draw(constantBufferData, constBuff, pImmediateContext, device);
	//}
}
