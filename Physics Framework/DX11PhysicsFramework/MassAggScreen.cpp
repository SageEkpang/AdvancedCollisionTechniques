#include "MassAggScreen.h"

MassAggScreen::MassAggScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	// NOTE: Screen Name
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_MASS_ARG_SCREEN;

}

MassAggScreen::~MassAggScreen()
{
	
}

void MassAggScreen::Update(float deltaTime)
{

}

void MassAggScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	
}


