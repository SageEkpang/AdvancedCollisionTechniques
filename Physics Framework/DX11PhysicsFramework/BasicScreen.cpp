#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	{
		m_CubeObject = new GameObjectEntity();
		m_CubeObject->m_Transform.m_Position = Vector3(15, 10, 30);
		m_CubeObject->m_Transform.m_Scale = Vector3(4, 4, 4);
		m_CubeObject->AddComponent<Mesh>()->Construct("cube", COLOUR_RED, device);
		m_CubeObject->AddComponent<BoxCollider>()->Construct(Vector3(4, 4, 4), device);
		// m_CubeObject->GetComponent<SphereCollider>()->m_RenderCollision = false;
		// m_CubeObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		// InsertObjectIntoList(m_CubeObject);
	}

	{
		m_SphereObject = new GameObjectEntity();
		m_SphereObject->m_Transform.m_Position = Vector3(10, 50, 30);
		m_SphereObject->m_Transform.m_Scale = Vector3(5, 5, 5);
		// m_SphereObject->AddComponent<Mesh>()->Construct("cube", COLOUR_RED, device);
		// m_SphereObject->AddComponent<BoxCollider>()->Construct(Vector3(5, 5, 5), device);
		m_SphereObject->AddComponent<MassAggregate>()->Construct("pyramidAlt", device);
		// m_SphereObject->GetComponent<SphereCollider>()->m_RenderCollision = false;
		m_SphereObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_DYNAMIC);
		InsertObjectIntoList(m_SphereObject);
	}

	//m_SATObject = new GameObjectEntity();
	//m_SATObject->m_Transform.m_Position = Vector3(10, 50, 30);
	//m_SATObject->m_Transform.m_Scale = Vector3(2, 2, 2);
	//m_SATObject->AddComponent<Mesh>()->ConstructHull("sphere", COLOUR_BLUE, device);
	//m_SATObject->AddComponent<EPACollider>()->ConstructHull("sphere", device);
	//m_SATObject->AddComponent<Rigidbody3DObject>()->Construct(1.f, Rigidbody3DMovementType::RIGIDBODY_3D_MOVEMENT_TYPE_STATIC);
	// InsertObjectIntoList(m_SATObject);

	//m_MassAggregateObject = new GameObjectEntity();
	//m_MassAggregateObject->m_Transform.m_Position = Vector3(0, 10, 30);
	//m_MassAggregateObject->m_Transform.m_Scale = Vector3(2, 2, 2);
	//m_MassAggregateObject->AddComponent<MassAggregate>()->Construct("cube", device);
	//InsertObjectIntoList(m_MassAggregateObject);


}

BasicScreen::~BasicScreen()
{
	// m_GameObjects.clear();
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
