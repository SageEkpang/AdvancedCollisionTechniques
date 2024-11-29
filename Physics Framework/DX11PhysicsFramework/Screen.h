#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "Structures.h"
#include "Constants.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "GameObject.h"

#include "PhysicUtility.h"

using namespace DirectX;

typedef struct ScreenInformation
{
	PhysicsScreenState physicsScreenState;
	ScreenState screenState;

	ScreenInformation() = default;

	ScreenInformation(PhysicsScreenState physicState, ScreenState screenState)
	{
		this->physicsScreenState = physicState;
		this->screenState = screenState;
	}

} ScreenInfo;

class Screen
{
protected:

	std::string m_ScreenName;
	ScreenInformation m_ScreenInformation = ScreenInformation();

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Base Class </summary>
	Screen(std::string screenName, ID3D11Device* device) { m_ScreenName = screenName; }

	/// <summary> Default Destructor for Base Class </summary>
	virtual ~Screen() { };


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	virtual void Update(Camera* camera, float deltaTime) { };

	/// <summary> Default Draw function for Class </summary>
	virtual void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext) { };


	// GETTER FUNCTION(s)
	inline std::string GetName() { return m_ScreenName; }
};

#endif
