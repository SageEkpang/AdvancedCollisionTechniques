#include "ScreenManager.h"
#include "StartUp.h"

void ScreenManager::Destroy()
{
	m_CurrentScreen = nullptr;
}

ScreenManager::ScreenManager(StartUp* startContent)
{
	// Set default values for everything
	m_CurrentPhysicsScreen = PhysicsScreenState::STATE_NONE;
	m_CurrentScreenState = ScreenState::SCREEN_CURRENT;

	// Load in Screen content
	for (size_t i = 0; startContent->GetScreenVector().size(); ++i)
	{
		m_Screens.push_back(startContent->GetScreenVector()[i]);
	}

	// Set the Current screen to the first screen in the vector array
	m_CurrentScreen = &m_Screens[0];
}

ScreenManager::~ScreenManager()
{
	Destroy();
}

void ScreenManager::Process()
{
	// TODO: Add the tick time for this
	m_CurrentScreen->Update(0);
}

void ScreenManager::Showcase()
{
	m_CurrentScreen->Draw();
}

void ScreenManager::TransitionScreen(PhysicsScreenState state, float deltaTime)
{
	int t_Index = 0;
	t_Index = (int)state;

	m_CurrentScreen = nullptr;
	m_CurrentScreen = &m_Screens[t_Index - 1]; // TODO: may need to call new here
}

void ScreenManager::TransitionScreen(ScreenState state, float deltaTime)
{
	int t_Index = 0;
	t_Index = (int)m_CurrentPhysicsScreen + (int)state;

	m_CurrentScreen = nullptr;
	m_CurrentScreen = &m_Screens[t_Index - 1];
	m_CurrentScreenState = ScreenState::SCREEN_CURRENT;
}
