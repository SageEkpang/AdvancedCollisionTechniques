#pragma once
#ifndef BASIC_SCREEN_H
#define BASIC_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"

class BasicScreen : public Screen
{
private:



public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	BasicScreen(std::string screenName);

	/// <summary> Default Destructor for Class </summary>
	~BasicScreen();



	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime);

	/// <summary> Default Draw function for Class </summary>
	void Draw();

};

#endif
