#ifndef BASIC_SCREEN_H
#define BASIC_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "ConstantBuffer.h"

// CUSTOM INCLUDE(s)
#include "ScreenEntity.h"
#include <vector>

// NOTE: Simple Collisions Colliding
class BasicScreen : public ScreenEntity
{
private:

	GameObjectEntity* m_SATObject;
	GameObjectEntity* m_CubeObject;
	GameObjectEntity* m_SphereObject;
	GameObjectEntity* m_MassAggregateObject;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	BasicScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~BasicScreen() override;

	// BASE FUNCTION(s)
	void Update(float deltaTime) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

};

#endif
