#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName)
	: Screen(screenName)
{
	// May need to add camera to this
	m_ScreenName = screenName;
	Screen::Screen(m_ScreenName);







}

BasicScreen::~BasicScreen()
{


	Screen::~Screen();
}

void BasicScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);



}

void BasicScreen::Draw()
{
	Screen::BeginRendering();





	Screen::EndRendering();
}
