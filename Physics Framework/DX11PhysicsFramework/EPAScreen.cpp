#include "EPAScreen.h"

EPAScreen::EPAScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_EPA_SCREEN;

	int m_ArraySize = 10;
	bool m_FlipFlop = 0;
	float m_XOffset = -1;
	float m_YOffset = 10;

	for (int i = 0; i < m_ArraySize; ++i)
	{
		if (i % (m_ArraySize / 2) == 0)
		{
			m_XOffset = 0;
			m_YOffset = i > 0 ? m_YOffset += 15 : m_YOffset;
			m_FlipFlop = !m_FlipFlop;
		}

		GameObjectEntity* t_temp;

		t_temp = new GameObjectEntity();
		t_temp->m_Transform.m_Position = Vector3((m_XOffset * 10) + (m_XOffset * 2), (m_YOffset), 30);
		t_temp->m_Transform.m_Scale = Vector3(5, 5, 5);

		++m_XOffset;

			t_temp->AddComponent<Rigidbody3DObject>()->Construct(1.0f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		if (m_FlipFlop == true)
		{
			t_temp->AddComponent<Mesh>()->Construct("cube", COLOUR_RED, device);
			t_temp->AddComponent<EPACollider>()->Construct("cube", device);
		}
		else
		{
			t_temp->AddComponent<Mesh>()->Construct("sphere", COLOUR_RED, device);
			t_temp->AddComponent<EPACollider>()->Construct("sphere", device);
		}


		InsertObjectIntoList(t_temp);
	}
}

EPAScreen::~EPAScreen()
{
	
}

void EPAScreen::Update(float deltaTime)
{
	ScreenEntity::Update(deltaTime);
}

void EPAScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	ScreenEntity::Draw(constantBufferData, constBuff, pImmediateContext, device);
}
