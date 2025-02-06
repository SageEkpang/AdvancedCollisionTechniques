#include "MassAggScreen.h"

MassAggScreen::MassAggScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_MASS_ARG_SCREEN;

	#pragma region PlaneObject

	// Plane Object
	{
		GameObject* t_PlaneObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_STATIC));
		Transform* t_PlaneTransform = new Transform();
		Render* t_PlaneRender = new Render(t_PlaneTransform);
		RigidbodyObject* t_PlaneRigidbody = new RigidbodyObject(t_PlaneTransform, 0.0f);
		Collider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform); // FIXME: Planar Collisions Tweaking Out

		// Transform
		t_PlaneObject->SetTransform(t_PlaneTransform);
		t_PlaneTransform->SetScale(100.0f, 1.0f, 100.0f);
		t_PlaneTransform->SetRotation(0.0f, 0.0f, 0.0f);
		t_PlaneTransform->SetPosition(0.0f, 0.0f, 10.0f);

		// Rigidbody 
		t_PlaneObject->SetRigidbody(t_PlaneRigidbody);
		t_PlaneRigidbody->SetMaterial(MaterialTypes::MATERIAL_SILICON);
		t_PlaneRigidbody->SetCollider(t_PlaneCollider);

		// Collision
		t_PlaneObject->SetCollider(t_PlaneCollider);
		t_PlaneCollider->SetCollisionGeometry("Resources\\OBJ\\CollisionPlane.obj", MATERIAL_WIREFRAME, device);

		// Rendering
		t_PlaneObject->SetRender(t_PlaneRender);
		t_PlaneRender->SetGeometryAndMaterial("Resources\\OBJ\\plane.obj", MATERIAL_SHINY, device);
		t_PlaneRender->SetTexture(L"Resources\\Textures\\floor.dds", device);

		InsertObjectIntoList(t_PlaneObject);
	}

	#pragma endregion

	// NOTE: Box Mass Aggregate System
	MassAggregate* t_BoxARG = new MassAggregate("Resources\\OBJ\\cube.obj", Vector3(0, 5, 3), 1.0f, 1, device);
	MassAggregate* t_PlaneARG = new MassAggregate("Resources\\OBJ\\CollisionPlane.obj", Vector3(0, 5, 10), 1.0f, 4, device);
	MassAggregate* t_PyramidARG = new MassAggregate("Resources\\OBJ\\Pyramid.obj", Vector3(10, 5, 10), 1.0f, 1, device);

	m_MassObjects.push_back(t_BoxARG);
	m_MassObjects.push_back(t_PlaneARG);
	m_MassObjects.push_back(t_PyramidARG);
}

MassAggScreen::~MassAggScreen()
{
	// NOTE: Deleting Objects within the Vector
	std::vector<MassAggregate*>::iterator itr = m_MassObjects.begin();
	for (itr; itr != m_MassObjects.end(); ++itr) { delete* itr; }

	// NOTE: Clear the object Vector
	m_MassObjects.clear();
	Screen::~Screen();
}

void MassAggScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
	MassSims(deltaTime);
}

void MassAggScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	Screen::Draw(constantBufferData, constBuff, pImmediateContext, device);
	for (auto& v : m_MassObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
}

// NOTE: Update for the Mass Objects
void MassAggScreen::MassSims(const float deltaTime)
{
	for (auto& v : m_MassObjects) { v->Update(deltaTime); }
}


