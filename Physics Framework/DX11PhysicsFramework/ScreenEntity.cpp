#include "ScreenEntity.h"

ScreenEntity::ScreenEntity(std::string screenName, ID3D11Device* device) : m_ScreenName(screenName)
{
	// Plane Object
	m_PlaneObject = new GameObjectEntity();
	m_PlaneObject->m_Transform.m_Position = Vector3(0, 0, 0);
	m_PlaneObject->m_Transform.m_Scale = Vector3(1000, 1, 1000);
	m_PlaneObject->m_Transform.m_Orientation = Quaternion4(0, 0, 0, 0);
	m_PlaneObject->AddComponent<Mesh>()->Construct("plane", "floor", device);
	m_PlaneObject->AddComponent<PlaneCollider>()->Construct(Vector3(1000, 1, 1000), device);
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

void ScreenEntity::Update(float deltaTime)
{
	// NOTE: Collision Checking
	for (int i = 0; i < m_GameObjects.size(); ++i)
	{
		for (int j = 0; j < m_GameObjects.size(); ++j)
		{
			if (i == j) continue;
			m_CollisionManager.CheckCollisions(m_GameObjects[i], m_GameObjects[j], m_CollisionSolutionMap).hasCollision;
		}
	}

	// NOTE: Collision Handling
	for (auto itr = m_CollisionSolutionMap.begin(); itr != m_CollisionSolutionMap.end(); ++itr)
	{
		auto collision_made_pair = std::make_pair((*itr).first.first, (*itr).first.second);
		CollisionContactManager::ResolveCollision(collision_made_pair.first, collision_made_pair.second, 0.5, m_CollisionSolutionMap[collision_made_pair]);
	}

	// NOTE: Clear Collision List
	m_CollisionSolutionMap.clear();

	// NOTE: Updating the Objects
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
