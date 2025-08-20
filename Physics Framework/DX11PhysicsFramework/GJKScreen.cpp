#include "GJKScreen.h"

GJKScreen::GJKScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_GJK_SCREEN;

	m_GJKCollider = new GJKCollider();

	// srand(time(NULL));
	for (int i = 0; i < 50; ++i)
	{
		// Cube Object
		//GameObject* t_CubeObject = new GameObject(Tag("Box", PhysicTag::PHYSICS_KINEMATIC));
		//Transform* t_CubeTransform = new Transform();
		//Render* t_CubeRender = new Render(t_CubeTransform);
		//RigidbodyObject* t_CubeRigidbody = new RigidbodyObject(t_CubeTransform, 1.0f);

		//Vector3 t_Rotation = Vector3(0, 0, 0);
		//Collider* t_CubeCollider = new BoxCollider(t_CubeTransform);

		//// Transform
		//t_CubeObject->SetTransform(t_CubeTransform);
		//t_CubeTransform->SetRotation(t_Rotation);
		//t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);

		//float t_RandX = (rand() % MAX_X) * 2 - (MAX_X / 2) - 10;
		//float t_RandY = rand() % MAX_X;
		//float t_RandZ = (rand() % MAX_Z) * 2 - (MAX_Z / 2) - 10;

		//t_CubeTransform->SetPosition(t_RandX, 10.0f + t_RandY, t_RandZ);

		//// Rigidbody 
		//t_CubeObject->SetRigidbody(t_CubeRigidbody);
		//t_CubeRigidbody->SetMaterial(MaterialTypes::MATERIAL_SILICON);
		//t_CubeRigidbody->SetCollider(t_CubeCollider);

		//// Collision
		//t_CubeObject->SetCollider(t_CubeCollider);
		//t_CubeCollider->FillVerticesArray("Resources\\OBJ\\cube.obj", t_CubeTransform);

		//// Rendering
		//t_CubeObject->SetRender(t_CubeRender);
		//t_CubeRender->SetGeometryAndMaterial("Resources\\OBJ\\cube.obj", MATERIAL_SHINY, device);
		//t_CubeRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

		// InsertObjectIntoList(t_CubeObject);
	}
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
