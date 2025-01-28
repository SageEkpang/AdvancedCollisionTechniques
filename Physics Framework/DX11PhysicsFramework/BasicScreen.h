#pragma once
#ifndef BASIC_SCREEN_H
#define BASIC_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"
#include "CollisionContact.h"

class BasicScreen : public Screen
{
private:

	CollisionContact* m_CollisionContact;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	BasicScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~BasicScreen();



	// HELPER FUNCTION(s)
	void ResolveCollision(GameObject* object1, GameObject* object2);




	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
};

#endif
