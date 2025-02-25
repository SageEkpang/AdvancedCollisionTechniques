#ifndef EPA_SCREEN_H
#define EPA_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"
#include "EPACollider.h"
#include "GJKCollider.h"
#include "Octree.h"

#include "CollisionContact.h"

class EPAScreen : public Screen
{
private:

	GJKCollider* m_GJKCollider;
	EPACollider* m_EPACollider;	
	Octree* m_Octree;
	bool m_UseOctree = false;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	EPAScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~EPAScreen();

	// HELPER FUNCTION(s)
	void ProcessEPA(const float deltaTime, ID3D11Device* device);

	// BASE FUNCTION(s)
	void Update(float deltaTime, ID3D11Device* device) override;
	void RandomImpulseDirection(float deltaTime);
};

#endif