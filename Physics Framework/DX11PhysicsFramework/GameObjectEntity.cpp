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
	// Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(m_Transform.m_Scale.x, m_Transform.m_Scale.y, m_Transform.m_Scale.z);

	// Rotation Matrix
	XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(m_Transform.m_Orientation.x, m_Transform.m_Orientation.y, m_Transform.m_Orientation.z, m_Transform.m_Orientation.w));

	// Position Matrix
	XMMATRIX Position = XMMatrixTranslation(m_Transform.m_Position.x, m_Transform.m_Position.y, m_Transform.m_Position.z);

	if (m_Transform.m_Parent == nullptr)
	{
		XMStoreFloat4x4(m_Transform.m_World, Scale * Orientation * Position);
	}
	else
	{
		XMStoreFloat4x4(m_Transform.m_Parent->m_World, m_Transform.GetWorldMatrix());
	}

	// Store Transform in Matrix

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
			// Component->Draw(constantBufferData, constBuff, pImmediateContext, device);
		}
	}
}