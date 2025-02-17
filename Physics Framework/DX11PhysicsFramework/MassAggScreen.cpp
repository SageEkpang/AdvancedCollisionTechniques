#include "MassAggScreen.h"

MassAggScreen::MassAggScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_MASS_ARG_SCREEN;

	// NOTE: Box Mass Aggregate System
	//MassAggregate* t_BoxARG = new MassAggregate("Resources\\OBJ\\tetrahedron.obj", Vector3(0, 5, 3), 1.0f, 1, device);
	//MassAggregate* t_PlaneARG = new MassAggregate("Resources\\OBJ\\tetrahedron.obj", Vector3(0, 5, 10), 1.0f, 4, device);
	//MassAggregate* t_PyramidARG = new MassAggregate("Resources\\OBJ\\tetrahedron.obj", Vector3(10, 5, 10), 1.0f, 1, device);
	//MassAggregate* t_TetrahARG = new MassAggregate("Resources\\OBJ\\tetrahedron.obj", Vector3(-10, 5, 10), 1.0f, 1, device);

	//m_MassObjects.push_back(t_BoxARG);
	//m_MassObjects.push_back(t_PlaneARG);
	//m_MassObjects.push_back(t_PyramidARG);
	//m_MassObjects.push_back(t_TetrahARG);

	Vector3 t_Position[5] = {
		Vector3(0, 5, 3),
		Vector3(0, 5, 10),
		Vector3(10, 5, 10),
		Vector3(-10, 5, 10)
	};

	for (int i = 0; i < 4; ++i)
	{
		MassAggregate* t_TempARG = new MassAggregate("Resources\\OBJ\\tetrahedron.obj", t_Position[i], 1.0f, 1, device);
		m_MassObjects.push_back(t_TempARG);
	}
}

MassAggScreen::~MassAggScreen()
{
	// NOTE: Deleting Objects within the Vector
	std::vector<MassAggregate*>::iterator itr = m_MassObjects.begin();
	for (itr; itr != m_MassObjects.end(); ++itr) { delete* itr; }

	// NOTE: Clear the object Vector
	m_MassObjects.clear();
	Screen::~Screen();
}

void MassAggScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
	for (auto& v : m_MassObjects) { v->Update(deltaTime); }
}

void MassAggScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	Screen::Draw(constantBufferData, constBuff, pImmediateContext, device);
	for (auto& v : m_MassObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
}


