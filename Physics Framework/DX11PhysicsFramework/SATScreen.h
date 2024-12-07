#pragma once
#ifndef SAT_SCREEN_H
#define SAT_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"

class SATScreen : public Screen
{
public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	SATScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~SATScreen();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
};

#endif
