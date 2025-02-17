#include "Screen.h"

Screen::~Screen()
{
	m_GameObjects.clear();
}

void Screen::Update(float deltaTime)
{
	if (!m_GameObjects.empty())
	{
		// Updating the Physics Objects Within the Respect
		for (auto& v : m_GameObjects) 
		{ 
			// NOTE: Apply Gravity to Objects
			v->GetRigidbody()->ApplyImpulse(-v->GetRigidbody()->GetGravity() * deltaTime);

			// NOTE: Resolve Position for the Floor // NOTE: "0" = floor
			if (v->GetTransform()->GetPosition().y - v->GetTransform()->GetScale().y / 2.0f < 0)
			{
				v->GetTransform()->SetPosition(Vector3(v->GetTransform()->GetPosition().x, 0 + v->GetTransform()->GetScale().y / 2.0f, v->GetTransform()->GetPosition().z));
				float t_Dampening = 0.01f;
				v->GetRigidbody()->SetVelocity(Vector3(v->GetRigidbody()->GetVelocity().x, -v->GetRigidbody()->GetVelocity().y * t_Dampening, v->GetRigidbody()->GetVelocity().z));
			}

			v->Update(deltaTime); 
		}
	}
}

void Screen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
	}
}

void Screen::InsertObjectIntoList(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}
