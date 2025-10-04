#ifndef GJK_SCREEN_H
#define GJK_SCREEN_H

// NEEDED INCLUDE(s)
#include "Constants.h"

// CUSTOM INCLUDE(s)
#include "ScreenEntity.h"
#include "GJKCollider.h"
#include "Octree.h"

class GJKScreen : public ScreenEntity
{
private:

	GameObjectEntity* m_CylinderObject;
	GameObjectEntity* m_PyramidObject;
	bool m_UseOctree = false;

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Class </summary>
	GJKScreen(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Class </summary>
	~GJKScreen() override;


	// BASE FUNCTION(s)
	/// <summary> Default Update function for Class </summary>
	void Update(float deltaTime) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

};

#endif
