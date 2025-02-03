#ifndef EPA_SCREEN_H
#define EPA_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"
#include "EPACollider.h"

class EPAScreen : public Screen
{
private:

	EPACollider* m_EPACollider;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	EPAScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~EPAScreen();


	// HELPER FUNCTION(s)
	void ResolveCollision(const float deltaTime);


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
};

#endif