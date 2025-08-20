#include "MassAggScreen.h"

MassAggScreen::MassAggScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	// NOTE: Screen Name
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_MASS_ARG_SCREEN;

	// NOTE: Box Mass Aggregate System
	Vector3 t_Position[] = {
		Vector3(0, 5, 3),
		Vector3(0, 5, 10),
		Vector3(10, 5, 10),
		Vector3(-10, 5, 10),
		Vector3(-5, 5, 5)
	};

	for (int i = 0; i < 5; ++i)
	{
		// MassAggregate* t_TempARG = new MassAggregate("Resources\\OBJ\\pyramid.obj", t_Position[i], 1.0f, 1, device);
		// m_MassObjects.push_back(t_TempARG);
	}
}

MassAggScreen::~MassAggScreen()
{
	// NOTE: Deleting Objects within the Vector
	std::vector<MassAggregate*>::iterator itr = m_MassObjects.begin();
	for (itr; itr != m_MassObjects.end(); ++itr) { delete* itr; }

	// NOTE: Clear the object Vector
	m_MassObjects.clear();
}

void MassAggScreen::Update(float deltaTime)
{
	// NOTE: Update the Mass Screen
	ScreenEntity::Update(deltaTime);
	for (auto& v : m_MassObjects) { v->Update(deltaTime); }
}

void MassAggScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	// NOTE: Draw the Mass Screen
	ScreenEntity::Draw(constantBufferData, constBuff, pImmediateContext, device);
	for (auto& v : m_MassObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
}


