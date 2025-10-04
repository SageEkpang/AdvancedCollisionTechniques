#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	{
		m_CubeObject = new GameObjectEntity();
		m_CubeObject->m_Transform.m_Position = Vector3(0, 15, 10);
		m_CubeObject->m_Transform.m_Scale = Vector3(4, 4, 4);
		m_CubeObject->AddComponent<Mesh>()->Construct("sphere", COLOUR_RED, device);
		m_CubeObject->AddComponent<SphereCollider>()->Construct(4, device);
		m_CubeObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		InsertObjectIntoList(m_CubeObject);
	}

	{
		m_SphereObject = new GameObjectEntity();
		m_SphereObject->m_Transform.m_Position = Vector3(0, 15, 10);
		m_SphereObject->m_Transform.m_Scale = Vector3(4, 4, 4);
		m_SphereObject->AddComponent<Mesh>()->Construct("sphere", COLOUR_RED, device);
		m_SphereObject->AddComponent<SphereCollider>()->Construct(4, device);
		m_SphereObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		InsertObjectIntoList(m_SphereObject);
	}



}

BasicScreen::~BasicScreen()
{
	
}

void BasicScreen::Update(float deltaTime)
{
	ScreenEntity::Update(deltaTime);

}

void BasicScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	ScreenEntity::Draw(constantBufferData, constBuff, pImmediateContext, device);
}
