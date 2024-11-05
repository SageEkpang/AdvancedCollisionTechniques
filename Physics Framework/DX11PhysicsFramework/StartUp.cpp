#include "StartUp.h"

#include "BasicScreen.h"

StartUp::StartUp()
{
	m_Screens.push_back(BasicScreen("BasicScreen"));
}

StartUp::~StartUp()
{
	m_Screens.clear();
}
