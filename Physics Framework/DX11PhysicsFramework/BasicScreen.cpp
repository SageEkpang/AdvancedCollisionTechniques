#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	m_DonutObject = new GameObjectEntity();
	m_DonutObject->m_Transform.m_Position = Vector3(0, 10, 10);
	m_DonutObject->m_Transform.m_Scale = Vector3(5, 5, 5);
	m_DonutObject->m_Transform.m_Orientation = Quaternion4(0, 0, 0, 0);

	m_DonutObject->AddComponent<Mesh>()->Construct("donut.obj", Vector4(255.0f, 0.0f, 0.0f, 1.f), device);
	m_DonutObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);

	InsertObjectIntoList(m_DonutObject);
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
