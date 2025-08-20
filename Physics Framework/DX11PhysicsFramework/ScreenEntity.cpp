#include "ScreenEntity.h"

ScreenEntity::ScreenEntity(std::string screenName, ID3D11Device* device) : m_ScreenName(screenName)
{
	// Plane Object
	m_PlaneObject = new GameObjectEntity();
	m_PlaneObject->m_Transform.m_Position = Vector3(0, 0, 0);
	m_PlaneObject->m_Transform.m_Scale = Vector3(1, 1, 1);
	m_PlaneObject->m_Transform.m_Orientation = Quaternion4(0, 0, 0, 0);
	m_PlaneObject->AddComponent<Mesh>()->Construct((char*)"Resources\\OBJ\\donut.obj", device);
	InsertObjectIntoList(m_PlaneObject);

}

ScreenEntity::~ScreenEntity()
{
	// NOTE: Delete Vector and Objects
	if (!m_GameObjects.empty())
	{
		std::vector<GameObjectEntity*>::iterator itr = m_GameObjects.begin();
		for (itr; itr != m_GameObjects.end(); ++itr) { delete* itr; }

		m_GameObjects.clear();
	}
}

void ScreenEntity::Update(float deltaTime, ID3D11Device* device)
{
	// Updating the Physics Objects
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects) 
		{ 
			v->Update(deltaTime); 
		}
	}
}

void ScreenEntity::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	// m_PlaneObject->Draw(constantBufferData, constBuff, pImmediateContext, device);
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects)
		{
			v->Draw(constantBufferData, constBuff, pImmediateContext, device); 
		}
	}
}

void ScreenEntity::InsertObjectIntoList(GameObjectEntity* gameObject)
{
	gameObject->Update(0);
	m_GameObjects.push_back(gameObject);
}
