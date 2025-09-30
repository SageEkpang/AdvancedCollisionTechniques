#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	{
		m_CubeObject = new GameObjectEntity();
		m_CubeObject->m_Transform.m_Position = Vector3(10, 5, 20);
		m_CubeObject->m_Transform.m_Scale = Vector3(4, 4, 4);
		m_CubeObject->AddComponent<Mesh>()->Construct("cube", COLOUR_RED, device);
		m_CubeObject->AddComponent<BoxCollider>()->Construct(Vector3(4, 4, 4), device);
		m_CubeObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		InsertObjectIntoList(m_CubeObject);
	}

	{
		m_MassAggregateObjectCube = new GameObjectEntity();
		m_MassAggregateObjectCube->m_Transform.m_Position = Vector3(10, 20, 20);
		m_MassAggregateObjectCube->m_Transform.m_Scale = Vector3(1, 1, 1);
		// m_MassAggregateObjectCube->AddComponent<Rigidbody3DObject>()->Construct(10.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		// m_MassAggregateObjectCube->AddComponent<BoxCollider>()->Construct(Vector3(2, 2, 2), device);
		// InsertObjectIntoList(m_MassAggregateObjectCube);
	}

	{
		m_MassAggregateObjectSmall = new GameObjectEntity();
		m_MassAggregateObjectSmall->m_Transform.m_Position = Vector3(10, 10, 30);
		m_MassAggregateObjectSmall->m_Transform.m_Scale = Vector3(1, 1, 1);
		// m_MassAggregateObjectSmall->AddComponent<Rigidbody3DObject>()->Construct(10.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		// m_MassAggregateObjectSmall->AddComponent<MassAggregate>()->Construct("cube", -50, 0.005, device); // -50
		// InsertObjectIntoList(m_MassAggregateObjectSmall);
	}
}

BasicScreen::~BasicScreen()
{
	
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
}
