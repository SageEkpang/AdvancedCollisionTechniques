#pragma once
#ifndef SAT_SCREEN_H
#define SAT_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// CUSTOM INCLUDE(s)
#include "ScreenEntity.h"

class SATScreen : public ScreenEntity
{
private:

	bool m_UseOctree = false;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	SATScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~SATScreen();

	// HELPER FUNCTION(s)
	void ProcessSAT(const float deltaTime, ID3D11Device* device);

	// BASE FUNCTION(s)
	void Update(float deltaTime, ID3D11Device* device) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;
};

#endif
