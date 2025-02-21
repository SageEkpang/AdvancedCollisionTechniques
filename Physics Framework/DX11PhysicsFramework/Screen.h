#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "Structures.h"
#include "Constants.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "GameObject.h"
#include "Timer.h"

using namespace DirectX;

// NOTE: PHYSICS SCREEN ENUM
enum PhysicsScreenState
{
	STATE_NONE = 0,
	STATE_BASIC_SCREEN,
	STATE_EPA_SCREEN,
	STATE_SAT_SCREEN,
	STATE_GJK_SCREEN,
	STATE_MASS_ARG_SCREEN
};

// NOTE: SCREEN STRUCT
typedef struct ScreenInformation
{
	PhysicsScreenState physicsScreenState;

	ScreenInformation() = default;

	ScreenInformation(PhysicsScreenState physicState)
	{
		this->physicsScreenState = physicState;
	}

} ScreenInfo;

class Screen
{
protected:

	// SCREEN VARIABLE(s)
	std::string m_ScreenName;
	ScreenInformation m_ScreenInformation = ScreenInformation();

	// OBJECT VARIABLE(s)
	std::vector<GameObject*> m_GameObjects;
	GameObject* m_GroundPlane;

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Base Class </summary>
	Screen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Base Class </summary>
	virtual ~Screen();



	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	virtual void Update(float deltaTime, ID3D11Device* device);

	/// <summary> Default Draw function for Class </summary>
	virtual void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

	// NOTE: This is the general collision response for objects
	virtual void ResolveCollision(RigidbodyObject* objectA, RigidbodyObject* objectB, float CoefRest, Vector3 normal);

	// HELPER FUNCTION(s)
	void InsertObjectIntoList(GameObject* gameObject);



	// GETTER FUNCTION(s)
	inline std::string GetName() { return m_ScreenName; }
};

#endif
