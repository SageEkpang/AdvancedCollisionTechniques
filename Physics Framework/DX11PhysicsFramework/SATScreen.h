#pragma once
#ifndef SAT_SCREEN_H
#define SAT_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"
#include "Octree.h"
#include "CollisionContact.h"
#include "OBBCollider.h"
#include "SATCollider.h"

class SATScreen : public Screen
{
private:

	SATCollider* m_SatCollider;
	Octree* m_Octree;
	Octant* m_Tree;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	SATScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~SATScreen();

	// HELPER FUNCTION(s)
	void ProcessSAT(const float deltaTime, ID3D11Device* device);
	void ResolveCollision(SATCollider* objectA, SATCollider* objectB, float CoefRest, Vector3 normal);

	// BASE FUNCTION(s)
	void Update(float deltaTime, ID3D11Device* device) override;
};

#endif
