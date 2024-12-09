#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	#pragma region Donut Object

	// Donut Object
	GameObject* t_DonutObject = new GameObject(Tag("Donut", PhysicTag::PHYSICS_STATIC));
	Render* t_DonutRender = new Render();
	Transform* t_DonutTransform = new Transform();

	RigidbodyObject* t_DonutRigidBody = new RigidbodyObject(t_DonutTransform, 0.0f);
	Collider* t_DonutCollider = new SphereCollider(t_DonutTransform, 5.0f);

	t_DonutObject->SetTransform(t_DonutTransform);
	t_DonutTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_DonutTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_DonutTransform->SetPosition(-5.0f, 10.0f, 10.0f);

	t_DonutObject->SetRigidbody(t_DonutRigidBody);
	t_DonutRigidBody->SetCollider(t_DonutCollider);
	t_DonutCollider->SetCollisionGeometry("Resources\\CollisionOBJ\\CollisionSphere.obj", MATERIAL_WIREFRAME, device);

	t_DonutObject->SetRender(t_DonutRender);
	t_DonutRender->SetGeometryAndMaterial("Resources\\OBJ\\donut.obj", MATERIAL_SHINY, device);
	t_DonutRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	// InsertObjectIntoList(t_DonutObject);

	#pragma endregion

	#pragma region Plane Object

	// Plane Object
	GameObject* t_PlaneObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_STATIC));
	Render* t_PlaneRender = new Render();
	Transform* t_PlaneTransform = new Transform();
	RigidbodyObject* t_PlaneRigidbody = new RigidbodyObject(t_PlaneTransform, 0.0f);
	Collider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform);

	// Transform
	t_PlaneObject->SetTransform(t_PlaneTransform);
	t_PlaneTransform->SetScale(100.0f, 1.0f, 100.0f);
	t_PlaneTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_PlaneTransform->SetPosition(0.0f, 0.0f, 10.0f);

	// Rigidbody 
	t_PlaneObject->SetRigidbody(t_PlaneRigidbody);
	t_PlaneRigidbody->SetCollider(t_PlaneCollider);

	// Collision
	t_PlaneObject->SetCollider(t_PlaneCollider);
	t_PlaneCollider->SetCollisionGeometry("Resources\\OBJ\\CollisionPlane.obj", MATERIAL_WIREFRAME, device);

	// Rendering
	t_PlaneObject->SetRender(t_PlaneRender);
	t_PlaneRender->SetGeometryAndMaterial("Resources\\OBJ\\plane.obj", MATERIAL_SHINY, device);
	t_PlaneRender->SetTexture(L"Resources\\Textures\\floor.dds", device);

	InsertObjectIntoList(t_PlaneObject);

	#pragma endregion

	#pragma region Head Object

	// Head Object
	GameObject* t_HeadObject = new GameObject(Tag("Head", PhysicTag::PHYSICS_STATIC));
	Render* t_HeadRender = new Render();
	Transform* t_HeadTransform = new Transform();
	RigidbodyObject* t_HeadRigidbody = new RigidbodyObject(t_HeadTransform, 0.0f);
	PlaneCollider* t_HeadCollider = new PlaneCollider(t_HeadTransform);

	t_HeadObject->SetTransform(t_HeadTransform);
	t_HeadTransform->SetScale(0.2f, 0.2f, 0.2f);
	t_HeadTransform->SetRotation(0.0f, 180.0f, 0.0f);
	t_HeadTransform->SetPosition(5.0f, 5.0f, 10.0f);

	t_HeadObject->SetRigidbody(t_HeadRigidbody);
	t_HeadRigidbody->SetCollider(t_HeadCollider);

	t_HeadObject->SetRender(t_HeadRender);
	t_HeadRender->SetGeometryAndMaterial("Resources\\OBJ\\joelModel.obj", MATERIAL_SHINY, device);
	t_HeadRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	// InsertObjectIntoList(t_HeadObject);

	#pragma endregion

	#pragma region Spike Ball Object

	// Spike Object
	GameObject* t_SpikeObject = new GameObject(Tag("Spike", PhysicTag::PHYSICS_STATIC));
	Render* t_SpikeRender = new Render();
	Transform* t_SpikeTransform = new Transform();
	RigidbodyObject* t_SpikeRigidbody = new RigidbodyObject(t_SpikeTransform, 0.0f);
	Collider* t_SpikeCollider = new SphereCollider(t_SpikeTransform, 10.0);

	// Transform
	t_SpikeObject->SetTransform(t_SpikeTransform);
	t_SpikeTransform->SetScale(1.0f, 1.0f, 1.0f);
	// t_SpikeTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_SpikeTransform->SetPosition(15.0f, 5.0f, 10.0f);

	// Rigidbody
	t_SpikeObject->SetRigidbody(t_SpikeRigidbody);
	t_SpikeObject->SetCollider(t_SpikeCollider);

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
	Screen::~Screen();
}

void BasicScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
}
