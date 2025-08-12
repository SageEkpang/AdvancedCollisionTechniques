#include "ScreenEntity.h"

ScreenEntity::ScreenEntity(std::string screenName, ID3D11Device* device) : m_ScreenName(screenName)
{
	// Plane Object
	GameObjectEntity m_PlaneObject;
	m_PlaneObject.m_Transform.m_Position = Vector3(0, 0, 0);
	m_PlaneObject.m_Transform.m_Scale = Vector3(10, 10, 10);
	m_PlaneObject.AddComponent<Mesh>()->Construct((char*)"Resources\\OBJ\\plane.obj", device);
	InsertObjectIntoList(&m_PlaneObject);
	m_GameObjects[0];

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
	if (!m_GameObjects.empty())
	{
		// Updating the Physics Objects
		for (auto& v : m_GameObjects) 
		{ 
			// NOTE: Update Object Regardless of Collision
			v->Update(deltaTime);

			//// NOTE: Apply Gravity to Objects
			//v->GetRigidbody()->ApplyImpulse(-v->GetRigidbody()->GetGravity() * deltaTime);

			//// NOTE: Resolve Position for the Floor // NOTE: "0" = floor
			//if (v->GetTransform()->GetPosition().y - v->GetTransform()->GetScale().y < 0)
			//{
			//	v->GetTransform()->SetPosition(Vector3(v->GetTransform()->GetPosition().x, 0 + v->GetTransform()->GetScale().y, v->GetTransform()->GetPosition().z));
			//	float t_Dampening = 0.0001f;
			//	v->GetRigidbody()->SetVelocity(Vector3(v->GetRigidbody()->GetVelocity().x, -v->GetRigidbody()->GetVelocity().y * t_Dampening, v->GetRigidbody()->GetVelocity().z));
			//}
		}
	}
}

void ScreenEntity::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
	}
}

void ScreenEntity::InsertObjectIntoList(GameObjectEntity* gameObject)
{
	m_GameObjects.push_back(gameObject);
}
