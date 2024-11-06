#include "Screen.h"

Screen::~Screen()
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects)
		{
			delete v;
			v = nullptr;
		}
		m_GameObjects.clear();
	}
}


