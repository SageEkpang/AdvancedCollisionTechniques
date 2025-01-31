#ifndef QUICK_HULL_SCREEN_H
#define QUICK_HULL_SCREEN_H


#define CONVHULL_3D_ENABLE

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"

class QuickHullScreen : public Screen
{
public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	QuickHullScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~QuickHullScreen();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
};

#endif
