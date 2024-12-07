#include "SATScreen.h"

SATScreen::SATScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_SAT_SCREEN;




}

SATScreen::~SATScreen()
{
	Screen::~Screen();
}

void SATScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
}
