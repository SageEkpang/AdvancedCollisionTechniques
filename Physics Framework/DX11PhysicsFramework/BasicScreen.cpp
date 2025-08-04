#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	m_CollisionContact = new CollisionContact();

	#pragma region Donut Object

	// Donut Object
	GameObject* t_DonutObject = new GameObject(Tag("Donut", PhysicTag::PHYSICS_KINEMATIC));
	Transform* t_DonutTransform = new Transform();
	Render* t_DonutRender = new Render(t_DonutTransform);

	RigidbodyObject* t_DonutRigidBody = new RigidbodyObject(t_DonutTransform, 1.0f);
	Collider* t_DonutCollider = new BoxCollider(t_DonutTransform);

	t_DonutObject->SetTransform(t_DonutTransform);
	t_DonutTransform->SetScale(3.0f, 3.0f, 3.0f);
	t_DonutTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_DonutTransform->SetPosition(0.0f, 5.0f, 10.0f);

	t_DonutObject->SetRigidbody(t_DonutRigidBody);
	t_DonutRigidBody->SetCollider(t_DonutCollider);
	t_DonutRigidBody->SetMass(1.0f);
	t_DonutCollider->SetCollisionGeometry("Resources\\CollisionOBJ\\CollisionSphere.obj", MATERIAL_WIREFRAME, device);

	t_DonutObject->SetRender(t_DonutRender);
	t_DonutRender->SetGeometryAndMaterial("Resources\\OBJ\\donut.obj", MATERIAL_SHINY, device);
	t_DonutRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	InsertObjectIntoList(t_DonutObject);

	#pragma endregion

	#pragma region Head Object

	// Head Object
	GameObject* t_HeadObject = new GameObject(Tag("Head", PhysicTag::PHYSICS_KINEMATIC));
	Transform* t_HeadTransform = new Transform();
	Render* t_HeadRender = new Render(t_HeadTransform);
	RigidbodyObject* t_HeadRigidbody = new RigidbodyObject(t_HeadTransform, 1.0f);
	PlaneCollider* t_HeadCollider = new PlaneCollider(t_HeadTransform);

	t_HeadObject->SetTransform(t_HeadTransform);
	t_HeadTransform->SetScale(3.0f, 3.0f, 3.0f);
	t_HeadTransform->SetRotation(0.0f, 180.0f, 0.0f);
	t_HeadTransform->SetPosition(-8.0f, 5.0f, 10.0f);

	t_HeadObject->SetRigidbody(t_HeadRigidbody);
	t_HeadRigidbody->SetCollider(t_HeadCollider);

	t_HeadObject->SetRender(t_HeadRender);
	t_HeadRender->SetGeometryAndMaterial("Resources\\OBJ\\Saucer.obj", MATERIAL_SHINY, device);
	t_HeadRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	InsertObjectIntoList(t_HeadObject);

	#pragma endregion

	#pragma region Spike Ball Object

	// Spike Object
	GameObject* t_SpikeObject = new GameObject(Tag("Spike", PhysicTag::PHYSICS_STATIC));
	Transform* t_SpikeTransform = new Transform();

	Render* t_SpikeRender = new Render(t_SpikeTransform);
	RigidbodyObject* t_SpikeRigidbody = new RigidbodyObject(t_SpikeTransform, 1.0f);
	Collider* t_SpikeCollider = new SphereCollider(t_SpikeTransform, 1.0);

	// Transform
	t_SpikeObject->SetTransform(t_SpikeTransform);
	t_SpikeTransform->SetScale(5.0f, 5.0f, 5.0f);
	t_SpikeTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_SpikeTransform->SetPosition(10.0f, 6.0f, 11.0f);

	// Rigidbody
	t_SpikeObject->SetRigidbody(t_SpikeRigidbody);
	t_SpikeRigidbody->SetMaterial(MaterialTypes::MATERIAL_STAINLESS_STEEL);
	t_SpikeRigidbody->SetCollider(t_SpikeCollider);

	// Collision
	t_SpikeRigidbody->SetCollider(t_SpikeCollider);
	t_SpikeCollider->SetCollisionGeometry("Resources\\OBJ\\CollisionSphere.obj", MATERIAL_WIREFRAME, device);

	// Rendering
	t_SpikeObject->SetRender(t_SpikeRender);
	t_SpikeRender->SetGeometryAndMaterial("Resources\\OBJ\\SpikeBall.obj", MATERIAL_MAX, device);
	t_SpikeRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	InsertObjectIntoList(t_SpikeObject);

	#pragma endregion
}

BasicScreen::~BasicScreen()
{
	
}

void BasicScreen::Update(float deltaTime, ID3D11Device* device)
{
	ScreenEntity::Update(deltaTime, device);
}

void BasicScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	ScreenEntity::Draw(constantBufferData, constBuff, pImmediateContext, device);



}
