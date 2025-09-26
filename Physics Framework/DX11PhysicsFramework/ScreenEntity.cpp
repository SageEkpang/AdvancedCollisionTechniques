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

			CollisionManager t_tempCollisionManager;
			CollisionManifold t_tempColMana = t_tempCollisionManager.CheckCollisions(m_GameObjects[i], m_GameObjects[j]);
			
			if (t_tempColMana.hasCollision == true)
			{
				for (int k = 0; k < t_tempColMana.points.size(); ++k)
				{
					CollisionManifold t_MultiColManifold;
					t_MultiColManifold.collisionNormal = t_tempColMana.points[k].collisionNormal;
					t_MultiColManifold.penetrationDepth = t_tempColMana.points[k].penetrationDepth;
					t_MultiColManifold.hasCollision = t_tempColMana.points[k].hasCollision;

					CollisionContactManager::ResolveCollision(m_GameObjects[i], m_GameObjects[j], 0.5, t_MultiColManifold);
				}
			}
		}
	}

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
