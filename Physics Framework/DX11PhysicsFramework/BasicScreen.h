#ifndef BASIC_SCREEN_H
#define BASIC_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "ConstantBuffer.h"

// CUSTOM INCLUDE(s)
#include "ScreenEntity.h"

// NOTE: Simple Collisions Colliding
class BasicScreen : public ScreenEntity
{
private:
public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	BasicScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~BasicScreen() override;

	// HELPER FUNCTION(s)

	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;

	/// <summary> Default Draw function for Class </summary>
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

};

#endif
