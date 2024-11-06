#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "Structures.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "GameObject.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

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
	ScreenInformation m_ScreenInformation;
	std::vector<GameObject*> m_GameObjects;
	ID3D11Device* device; // TODO: Find a way to add this to the screens

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Base Class </summary>
	Screen(std::string screenName) { m_ScreenName = screenName; }

	/// <summary> Default Destructor for Base Class </summary>
	virtual ~Screen();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	virtual void Update(Camera* camera, float deltaTime) { }

	/// <summary> Default Draw function for Class </summary>
	virtual void Draw() { } //TODO: May need to change this


	// GETTER FUNCTION(s)
	inline std::string GetName() { return m_ScreenName; }
};

#endif
