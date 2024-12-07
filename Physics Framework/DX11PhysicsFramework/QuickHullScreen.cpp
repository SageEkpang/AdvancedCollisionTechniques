#include "QuickHullScreen.h"

QuickHullScreen::QuickHullScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_QUICK_HULL_SCREEN;





}

QuickHullScreen::~QuickHullScreen()
{
	Screen::~Screen();
}

void QuickHullScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
}
