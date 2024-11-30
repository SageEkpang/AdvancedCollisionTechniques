#pragma once
#ifndef BASIC_SCREEN_H
#define BASIC_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "Screen.h"

class BasicScreen : public Screen
{
private:

	std::vector<GameObject*> m_Objects;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	BasicScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~BasicScreen();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(Camera* camera, float deltaTime) override;

	/// <summary> Default Draw function for Class </summary>
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext) override;
};

#endif
