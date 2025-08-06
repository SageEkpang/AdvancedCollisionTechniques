#ifndef COMPONENT_H
#define COMPONENT_H

// NEEDED INCLUDE(s)
#include "ConstantBuffer.h"
#include <d3d11.h>
#include <iostream>

class GameObjectEntity;

// NOTE: INTERFACE
class ComponentEntity
{
public:

	GameObjectEntity* m_Owner = nullptr;

protected: // PROTECTED VARIABLE(s)

	unsigned short m_ID;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	ComponentEntity() : m_ID(0) {}
	virtual ~ComponentEntity() { m_Owner = nullptr; }

	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime) { }
	virtual void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) { }
};

#endif