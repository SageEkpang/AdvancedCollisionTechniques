#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "Structures.h"

typedef struct ScreenInformation
{
	PhysicsScreenState physicsScreenState;
	ScreenState screenState;

	ScreenInformation() = default;

	ScreenInformation(PhysicsScreenState physicState, ScreenState screenState)
	{
		this->physicsScreenState = physicState;
		this->screenState = screenState;
	}

} ScreenInfo;


class Screen
{
protected:

	std::string m_ScreenName;
	ScreenInformation m_ScreenInformation;

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Base Class </summary>
	Screen(std::string screenName) { m_ScreenName = screenName; }

	/// <summary> Default Destructor for Base Class </summary>
	virtual ~Screen() { };



	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	virtual void Update(float deltaTime) { }

	/// <summary> Default Draw function for Class </summary>
	virtual void Draw() { }



	// GETTER FUNCTION(s)
	inline std::string GetName() { return m_ScreenName; }


	// SETTER FUNCTION(s)





};

#endif
