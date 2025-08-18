#ifndef SCREEN_ENTITY_H
#define SCREEN_ENTITY_H

#include "Camera.h"
#include "GameObjectEntity.h"
#include "Timer.h"

using namespace DirectX;

// NOTE: PHYSICS SCREEN ENUM
enum PhysicsScreenState
{
	STATE_NONE = 0,
	STATE_BASIC_SCREEN,
	STATE_EPA_SCREEN,
	STATE_SAT_SCREEN,
	STATE_GJK_SCREEN,
	STATE_MASS_ARG_SCREEN
};

// NOTE: SCREEN STRUCT
typedef struct ScreenInformation
{
	PhysicsScreenState physicsScreenState;

	ScreenInformation() = default;

	ScreenInformation(PhysicsScreenState physicState)
	{
		this->physicsScreenState = physicState;
	}

} ScreenInfo;

class ScreenEntity
{
private:

	GameObjectEntity* m_PlaneObject;

protected:

	// SCREEN VARIABLE(s)
	std::string m_ScreenName;
	ScreenInformation m_ScreenInformation = ScreenInformation();

	// OBJECT VARIABLE(s)
	std::vector<GameObjectEntity*> m_GameObjects;

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Base Class </summary>
	ScreenEntity(std::string screenName, ID3D11Device* device);

	/// <summary> Default Destructor for Base Class </summary>
	virtual ~ScreenEntity();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	virtual void Update(float deltaTime, ID3D11Device* device);

	/// <summary> Default Draw function for Class </summary>
	virtual void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

	// HELPER FUNCTION(s)
	void InsertObjectIntoList(GameObjectEntity* gameObject);



	// GETTER FUNCTION(s)
	inline std::string GetName() { return m_ScreenName; }
};

#endif
