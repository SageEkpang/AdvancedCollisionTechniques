#pragma once
#ifndef GJK_SCREEN_H
#define GJK_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"

class GJKScreen : public Screen
{
public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	GJKScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~GJKScreen();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
};

#endif
