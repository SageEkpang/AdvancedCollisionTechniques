#pragma once
#ifndef GJK_SCREEN_H
#define GJK_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "ScreenEntity.h"
#include "GJKCollider.h"
#include "Octree.h"

#include "CollisionContact.h"

class GJKScreen : public ScreenEntity
{
private:

	GJKCollider* m_GJKCollider;
	bool m_UseOctree = false;

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Class </summary>
	GJKScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~GJKScreen() override;

	// HELPER FUNCTION(s)
	void ProcessGJK(const float deltaTime);

	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime, ID3D11Device* device) override;
	void RandomImpulseDirection(float deltaTime);
};

#endif
