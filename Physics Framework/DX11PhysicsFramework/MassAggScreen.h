#pragma once
#ifndef MASS_AGG_SCREEN_H
#define MASS_AGG_SCREEN_H

// NEEDED INCLUDE(s)
#include "Structures.h"
#include "Constants.h"

// CUSTOM INCLUDE(s)
#include "ScreenEntity.h"
#include "MassAggregate.h"

class MassAggScreen : public ScreenEntity
{
private:

	std::vector<MassAggregate*> m_MassObjects;

public:

	// CLASS FUNCTION(s)
	MassAggScreen(std::string screenName, ID3D11Device* device);
	~MassAggScreen() override;

	// BASE FUNCTION(s)
	void Update(float deltaTime, ID3D11Device* device) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;
};

#endif