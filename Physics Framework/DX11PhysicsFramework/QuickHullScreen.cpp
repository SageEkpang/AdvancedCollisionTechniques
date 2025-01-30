#include "QuickHullScreen.h"

QuickHullScreen::QuickHullScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_QUICK_HULL_SCREEN;

	// Spike Object
	GameObject* t_SpikeObject = new GameObject(Tag("Spike", PhysicTag::PHYSICS_STATIC));
	Transform* t_SpikeTransform = new Transform();

	Render* t_SpikeRender = new Render(t_SpikeTransform);
	RigidbodyObject* t_SpikeRigidbody = new RigidbodyObject(t_SpikeTransform, 1.0f);
	Collider* t_SpikeCollider = new BoxCollider(t_SpikeTransform);

	// Transform
	t_SpikeObject->SetTransform(t_SpikeTransform);
	t_SpikeTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_SpikeTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_SpikeTransform->SetPosition(15.0f, 5.0f, 10.0f);

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
}

QuickHullScreen::~QuickHullScreen()
{
	Screen::~Screen();
}

void QuickHullScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);







}
