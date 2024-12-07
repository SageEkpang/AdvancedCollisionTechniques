#include "GJKScreen.h"

GJKScreen::GJKScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_GJK_SCREEN;





}

GJKScreen::~GJKScreen()
{
	Screen::~Screen();
}

void GJKScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
}
