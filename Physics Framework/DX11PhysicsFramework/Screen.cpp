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
			v->Update(deltaTime); 
		}

		for (auto& v : m_GameObjects)
		{
			// Collision Code here
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
