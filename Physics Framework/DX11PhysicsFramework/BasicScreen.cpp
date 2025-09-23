#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	m_GameObjects.clear();

	m_CubeObject = new GameObjectEntity();
	m_CubeObject->m_Transform.m_Position = Vector3(0, 10, 30);
	m_CubeObject->m_Transform.m_Scale = Vector3(5, 5, 5);
	m_CubeObject->AddComponent<Mesh>()->Construct("cone.obj", COLOUR_RED, device);
	m_CubeObject->AddComponent<EPACollider>()->Construct((char*)"Resources\\OBJ\\cone.obj", device);
	// m_CubeObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
	InsertObjectIntoList(m_CubeObject);


	m_SATObject = new GameObjectEntity();
	m_SATObject->m_Transform.m_Position = Vector3(0, 50, 30);
	m_SATObject->m_Transform.m_Scale = Vector3(5, 5, 5);

	m_SATObject->AddComponent<Mesh>()->Construct("cube.obj", COLOUR_BLUE, device);


	m_SATObject->AddComponent<EPACollider>()->Construct((char*)"Resources\\OBJ\\cube.obj", device);
	m_SATObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
	InsertObjectIntoList(m_SATObject);

	srand(time(NULL));

	//int m_ArraySize = 10;
	//bool m_FlipFlop = 0;
	//float m_XOffset = -1;
	//float m_YOffset = 10;

	//m_GameObjects.resize(m_ArraySize);
	//for (int i = 0; i < m_ArraySize; ++i)
	//{
	//	if (i % (m_ArraySize / 2) == 0) 
	//	{
	//		m_XOffset = 0;
	//		m_YOffset = i > 0 ? m_YOffset += 15 : m_YOffset;
	//		m_FlipFlop = !m_FlipFlop; 
	//	}

	//	m_GameObjects[i] = new GameObjectEntity();
	//	m_GameObjects[i]->m_Transform.m_Position = Vector3((m_XOffset * 10) + (m_XOffset * 2), (m_YOffset), 30);
	//	m_GameObjects[i]->m_Transform.m_Scale = Vector3(5, 5, 5);

	//	++m_XOffset;

	//	m_GameObjects[i]->AddComponent<Mesh>()->Construct("cube.obj", COLOUR_RED, device);
	//	m_GameObjects[i]->AddComponent<BoxCollider>()->Construct(Vector3(5, 5, 5), device);

	//	//if (m_FlipFlop == true)
	//	//{
	//	//	m_GameObjects[i]->AddComponent<Mesh>()->Construct("cube.obj", COLOUR_RED, device);
	//	//	m_GameObjects[i]->AddComponent<BoxCollider>()->Construct(Vector3(5, 5, 5), device);
	//	//}
	//	//else
	//	//{
	//	//	m_GameObjects[i]->AddComponent<Mesh>()->Construct("sphere.obj", COLOUR_RED, device);
	//	//	m_GameObjects[i]->AddComponent<SphereCollider>()->Construct(5.f, device);
	//	//}

	//	m_GameObjects[i]->AddComponent<Rigidbody3DObject>()->Construct(0.1f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);

	//	InsertObjectIntoList(m_GameObjects[i]);
	//}
}

BasicScreen::~BasicScreen()
{
	m_GameObjects.clear();
}

void BasicScreen::Update(float deltaTime)
{
	ScreenEntity::Update(deltaTime);

	if (GetAsyncKeyState(VK_SPACE))
	{
		for (auto& v : m_GameObjects)
		{
			v->GetComponent<Rigidbody3DObject>()->ApplyImpulseX((rand() % 5) - 2.5f);
			v->GetComponent<Rigidbody3DObject>()->ApplyImpulseY((rand() % 5) - 2.5f);
			v->GetComponent<Rigidbody3DObject>()->ApplyImpulseZ((rand() % 5) - 2.5f);
		}
	}

}

void BasicScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	ScreenEntity::Draw(constantBufferData, constBuff, pImmediateContext, device);

	if (m_CubeObject->FindChildComponent<ColliderEntity>()->m_HasCollided == false)
	{
		printf("No Collision");
	}



}
