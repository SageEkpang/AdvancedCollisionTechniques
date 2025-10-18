#include "ScreenEntity.h"

bool ScreenEntity::m_ActivateOctree = false;

ScreenEntity::ScreenEntity(std::string screenName, ID3D11Device* device) : m_ScreenName(screenName)
{
	// Plane Object
	m_PlaneObjectBasic = new GameObjectEntity();
	m_PlaneObjectBasic->m_Transform.m_Position = Vector3(0, 0, 0);
	m_PlaneObjectBasic->m_Transform.m_Scale = Vector3(500, 1, 500);
	m_PlaneObjectBasic->AddComponent<Mesh>()->Construct("plane", "floor", device);
	m_PlaneObjectBasic->AddComponent<PlaneCollider>()->Construct(Vector3(500, 1, 500), device);
	m_PlaneObjectBasic->GetComponent<PlaneCollider>()->m_IsCollideable = true;
	InsertObjectIntoList(m_PlaneObjectBasic);

	// Wall Objects
	m_LeftWallObject = new GameObjectEntity();
	m_LeftWallObject->m_Transform.m_Position = Vector3(260, 0, 0);
	m_LeftWallObject->m_Transform.m_Scale = Vector3(10, 100, 250);
	m_LeftWallObject->AddComponent<BoxCollider>()->Construct(Vector3(10, 100, 250), device);
	m_LeftWallObject->GetComponent<BoxCollider>()->m_IsCollideable = false;
	InsertObjectIntoList(m_LeftWallObject);

	m_RightWallObject = new GameObjectEntity();
	m_RightWallObject->m_Transform.m_Position = Vector3(-260, 0, 0);
	m_RightWallObject->m_Transform.m_Scale = Vector3(10, 100, 250);
	m_RightWallObject->AddComponent<BoxCollider>()->Construct(Vector3(10, 100, 250), device);
	m_RightWallObject->GetComponent<BoxCollider>()->m_IsCollideable = false;
	InsertObjectIntoList(m_RightWallObject);

	m_BackWallObject = new GameObjectEntity();
	m_BackWallObject->m_Transform.m_Position = Vector3(0, 0, 260);
	m_BackWallObject->m_Transform.m_Scale = Vector3(250, 100, 10);
	m_BackWallObject->AddComponent<BoxCollider>()->Construct(Vector3(250, 100, 10), device);
	m_BackWallObject->GetComponent<BoxCollider>()->m_IsCollideable = false;
	InsertObjectIntoList(m_BackWallObject);

	// Octree

	// m_Octree = new Octree(Vector3(0, 0, 0), 100, 3);

	m_Octree = new Octant();
	m_Octree = Octree::BuildOctree(Vector3(0, 0, 0), 100, 3);

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

	if (m_ActivateOctree == true)
	{
		// NOTE: Insert Game Objects into the Octree
		for (int i = 0; i < m_GameObjects.size(); ++i) { Octree::P_InsertEntity(m_Octree, *&m_GameObjects[i]); }

		// NOTE: Update Game Objects in Tree
		Octree::P_UpdateTree(m_Octree, deltaTime);

		// NOTE: Query Game Objects in Tree
		Octree::P_QueryTree(m_Octree);

		// NOTE: Clear Octants
		for (int i = 0; i < 8; ++i) { Octree::P_ClearOctant(m_Octree, i); }

		return;
	}

	// NOTE: Will Not get here

	// NOTE: Collision Checking
	for (int i = 0; i < m_GameObjects.size(); ++i)
	{
		for (int j = 0; j < m_GameObjects.size(); ++j)
		{
			if (i == j) continue;
			m_CollisionManager.CheckCollisions(m_GameObjects[i], m_GameObjects[j], m_CollisionSolutionMap);
		}
	}

	// NOTE: Collision Handling
	for (auto itr = m_CollisionSolutionMap.begin(); itr != m_CollisionSolutionMap.end(); ++itr)
	{
		auto collision_made_pair = std::make_pair((*itr).first.first, (*itr).first.second);
		CollisionContactManager::ResolveCollision(&collision_made_pair.first, &collision_made_pair.second, 0.1, m_CollisionSolutionMap[collision_made_pair]);
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
