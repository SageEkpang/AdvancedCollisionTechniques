#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	// m_Transform = Transform();
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
	// Update the Transform of the Object
	m_Transform.Update(deltaTime);

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