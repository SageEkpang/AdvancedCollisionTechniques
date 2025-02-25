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

class EPAScreen : public Screen
{
private:

	GJKCollider* m_GJKCollider;
	EPACollider* m_EPACollider;	
	Octree* m_Octree;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	EPAScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~EPAScreen();

	// HELPER FUNCTION(s)
	void ProcessEPA(const float deltaTime, ID3D11Device* device);
	void CreatePhysicsObject(ID3D11Device* device);
	void ResolveCollision(GameObject* objectA, GameObject* objectB, float CoefRest, Vector3 normal);

	// BASE FUNCTION(s)
	void Update(float deltaTime, ID3D11Device* device) override;
};

#endif