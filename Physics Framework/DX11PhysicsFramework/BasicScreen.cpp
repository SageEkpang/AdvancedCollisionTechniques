#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	// NOTE: Donut
	m_DonutObject = new GameObjectEntity();
	m_DonutObject->m_Transform.m_Position = Vector3(0, 10, 30);
	m_DonutObject->m_Transform.m_Scale = Vector3(5, 5, 5);

	m_DonutObject->AddComponent<Mesh>()->Construct("donut.obj", COLOUR_RED, device);
	// m_DonutObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
	InsertObjectIntoList(m_DonutObject);

	// NOTE: Sphere
	m_SphereObject = new GameObjectEntity();
	m_SphereObject->m_Transform.m_Position = Vector3(10, 10, 30);
	m_SphereObject->m_Transform.m_Scale = Vector3(1, 1, 1);
	
	m_SphereObject->AddComponent<Mesh>()->Construct("sphere.obj", COLOUR_GREEN, device);
	m_SphereObject->AddComponent<SphereCollider>()->Construct(4.f, device);
	InsertObjectIntoList(m_SphereObject);

	// NOTE: Cube
	m_CubeObject = new GameObjectEntity();
	m_CubeObject->m_Transform.m_Position = Vector3(-10, 10, 30);
	m_CubeObject->m_Transform.m_Scale = Vector3(1, 1, 1);
	m_CubeObject->AddComponent<Mesh>()->Construct("cube.obj", COLOUR_BLUE, device);
	// m_CubeObject->AddComponent<BoxCollider>()->Construct(Vector3(5, 5, 5), device);
	// InsertObjectIntoList(m_CubeObject);

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
