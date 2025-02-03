#include "EPAScreen.h"

EPAScreen::EPAScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)

{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_EPA_SCREEN;
	m_EPACollider = new EPACollider();

#pragma region Cube1
	{
		// Cube Object
		GameObject* t_CubeObject = new GameObject(Tag("Box", PhysicTag::PHYSICS_KINEMATIC));
		Transform* t_CubeTransform = new Transform();
		Render* t_CubeRender = new Render(t_CubeTransform);
		RigidbodyObject* t_CubeRigidbody = new RigidbodyObject(t_CubeTransform, 1.0f);

		Vector3 t_Rotation = Vector3(0, 0, 0);
		Collider* t_CubeCollider = new BoxCollider(t_CubeTransform);

		// Transform
		t_CubeObject->SetTransform(t_CubeTransform);
		t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);
		t_CubeTransform->SetRotation(t_Rotation);
		t_CubeTransform->SetPosition(3.0f, 3.0f, 10.0f);

		// Rigidbody 
		t_CubeObject->SetRigidbody(t_CubeRigidbody);
		t_CubeRigidbody->SetMaterial(MaterialTypes::MATERIAL_SILICON);
		t_CubeRigidbody->SetCollider(t_CubeCollider);

		// Collision
		t_CubeObject->SetCollider(t_CubeCollider);
		t_CubeCollider->FillVerticesArray("Resources\\OBJ\\cube.obj", t_CubeTransform);
		// t_CubeCollider->SetCollisionGeometry("Resources\\OBJ\\CollisionCube.obj", MATERIAL_WIREFRAME, device);

		// Rendering
		t_CubeObject->SetRender(t_CubeRender);
		t_CubeRender->SetGeometryAndMaterial("Resources\\OBJ\\cube.obj", MATERIAL_SHINY, device);
		t_CubeRender->SetTexture(L"Resources\\Textures\\stone.dds", device);


		InsertObjectIntoList(t_CubeObject);
	}
#pragma endregion

#pragma region Cube2
	{
		// Cube Object
		GameObject* t_CubeObject = new GameObject(Tag("Box", PhysicTag::PHYSICS_KINEMATIC));
		Transform* t_CubeTransform = new Transform();
		Render* t_CubeRender = new Render(t_CubeTransform);
		RigidbodyObject* t_CubeRigidbody = new RigidbodyObject(t_CubeTransform, 1.0f);

		Vector3 t_Rotation = Vector3(0, 0, 0);
		Collider* t_CubeCollider = new BoxCollider(t_CubeTransform);

		// Transform
		t_CubeObject->SetTransform(t_CubeTransform);
		t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);
		t_CubeTransform->SetRotation(t_Rotation);
		t_CubeTransform->SetPosition(2.0f, 100.0f, 10.0f);

		// Rigidbody 
		t_CubeObject->SetRigidbody(t_CubeRigidbody);
		t_CubeRigidbody->SetMaterial(MaterialTypes::MATERIAL_SILICON);
		t_CubeRigidbody->SetCollider(t_CubeCollider);

		// Collision
		t_CubeObject->SetCollider(t_CubeCollider);
		t_CubeCollider->FillVerticesArray("Resources\\OBJ\\cube.obj", t_CubeTransform);

		// Rendering
		t_CubeObject->SetRender(t_CubeRender);
		t_CubeRender->SetGeometryAndMaterial("Resources\\OBJ\\cube.obj", MATERIAL_SHINY, device);
		t_CubeRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

		InsertObjectIntoList(t_CubeObject);
	}
#pragma endregion




}

EPAScreen::~EPAScreen()
{
	Screen::~Screen();
}

void EPAScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
}

void EPAScreen::ResolveCollision(const float deltaTime)
{

}
