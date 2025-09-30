#include "GJKScreen.h"

GJKScreen::GJKScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_GJK_SCREEN;

	// NOTE: Cylinder
	m_CylinderObject = new GameObjectEntity();
	m_CylinderObject->m_Transform.m_Position = Vector3(0, 10, 30);
	m_CylinderObject->m_Transform.m_Scale = Vector3(5, 5, 5);
	m_CylinderObject->AddComponent<Mesh>()->Construct("cylinder.obj", COLOUR_RED, device);
	m_CylinderObject->AddComponent<BoxCollider>()->Construct(Vector3(5, 5, 5), device);
	// m_CylinderObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
	// InsertObjectIntoList(m_CylinderObject);

	// NOTE: Pyramid
	m_PyramidObject = new GameObjectEntity();
	m_PyramidObject->m_Transform.m_Position = Vector3(-20, 10, 30);
	m_PyramidObject->m_Transform.m_Scale = Vector3(2, 2, 2);
	m_PyramidObject->AddComponent<Mesh>()->Construct("cone.obj", COLOUR_WHITE, device);
	m_PyramidObject->AddComponent<BoxCollider>()->Construct(Vector3(2, 2, 2), device);
	// m_PyramidObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
	// InsertObjectIntoList(m_PyramidObject);
}

GJKScreen::~GJKScreen()
{
	
}

void GJKScreen::Update(float deltaTime)
{
	ScreenEntity::Update(deltaTime);
	// ProcessGJK(deltaTime);
}

void GJKScreen::RandomImpulseDirection(float deltaTime)
{
	//for (auto& v : m_GameObjects)
	//{
	//	//float t_RandX = (rand() % 10) * 2 - 10;
	//	//float t_RandY = rand() % 3;
	//	//float t_RandZ = (rand() % 10) * 2 - 10;

	//	// v->GetRigidbody()->ApplyImpulse(Vector3(t_RandX, t_RandY, t_RandZ));
	//}
}

void GJKScreen::ProcessGJK(const float deltaTime)
{
	//if (GetAsyncKeyState(VK_RETURN)) { RandomImpulseDirection(deltaTime); }

	//if ((GetAsyncKeyState(VK_C) && m_UseOctree == true) & 0x0001)
	//{
	//	m_UseOctree = false;
	//}
	//else if ((GetAsyncKeyState(VK_C) && m_UseOctree == false) & 0x0001)
	//{
	//	m_UseOctree = true;
	//}

	




}
