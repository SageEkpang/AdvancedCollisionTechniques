#pragma once
#ifndef SAT_SCREEN_H
#define SAT_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"
#include "CollisionContact.h"
#include "OBBCollider.h"
#include "SATCollider.h"

class SATScreen : public Screen
{
private:

	CollisionContact* m_CollisionContact;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	SATScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~SATScreen();


	// HELPER FUNCTION(s)

	// TODO: Put this in collision class
	void ResolveCollision(const float deltaTime);



	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
};

#endif
