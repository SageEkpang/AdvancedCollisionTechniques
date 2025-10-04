#ifndef EPA_SCREEN_H
#define EPA_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"

// CUSTOM INCLUDE(s)
#include "ScreenEntity.h"

class EPAScreen : public ScreenEntity
{
private:
public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	EPAScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~EPAScreen();


	// BASE FUNCTION(s)
	void Update(float deltaTime) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

};

#endif