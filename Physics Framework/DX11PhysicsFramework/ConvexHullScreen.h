#pragma once
#ifndef CONVEX_HULL_SCREEN_H
#define CONVEX_HULL_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"

class ConvexHullScreen : public Screen
{
public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	ConvexHullScreen(std::string screenName, ID3D11Device* device);

	///<summary> Default Destructor for Class </summary>
	~ConvexHullScreen();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
};

#endif
