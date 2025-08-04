#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	// NOTE: Parent and Children Variable(s)

	// NOTE: Transform Variable(s)
	//m_Transform.position = OKVector2<float>(0.f, 0.f);
	//m_Transform.scale = OKVector2<float>(1.f, 1.f);
	//m_Transform.rotation = 0.f;
	m_Components.clear();
}

GameObjectEntity::~GameObjectEntity()
{
	if (!m_Components.empty())
	{
		for (auto& [ComponentType, Component] : m_Components)
		{
			if (Component == nullptr) { continue; }

			delete Component;
			Component = nullptr;
		}
	}

	m_Components.clear();
}

void GameObjectEntity::Update(float deltaTime)
{
	// TODO: PARENT FUNCTIONALITY
	
	// NOTE: Update the Components
	if (!m_Components.empty())
	{
		for (auto& [ComponentType, Component] : m_Components)
		{
			Component->Update(deltaTime);
		}
	}
}

void GameObjectEntity::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	// NOTE: Draw the Components
	if (!m_Components.empty())
	{
		for (auto& [ComponentType, Component] : m_Components)
		{
			Component->Draw(constantBufferData, constBuff, pImmediateContext, device);
		}
	}
}