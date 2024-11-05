#pragma once
#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

// NEEDED INCLUDE(s)
#include "Structures.h"
#include "Screen.h"


//  CUSTOM INCLUDE(s) / FORWARD DEC(s)
class StartUp;

class ScreenManager
{
private:

	Screen* m_CurrentScreen = nullptr;
	std::vector<Screen> m_Screens;

	ScreenState m_CurrentScreenState;
	PhysicsScreenState m_CurrentPhysicsScreen;

	void Destroy();

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	ScreenManager(StartUp* startContent);

	/// <summary> Default Destructor for Class </summary>
	~ScreenManager();



	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Process();

	/// <summary> Default Draw function for Class </summary>
	void Showcase();



	// EXTRA FUNCTION(s)

	/// <summary> Transitions Screens either using the Physics Screen State or the Screen State </summary>
	void TransitionScreen(PhysicsScreenState state, float deltaTime);
	void TransitionScreen(ScreenState state, float deltaTime);




};

#endif

