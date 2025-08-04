#include "SATScreen.h"

SATScreen::SATScreen(std::string screenName, ID3D11Device* device) : ScreenEntity(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_SAT_SCREEN;

	// NOTE: Init 50 Objects for Testing Collosions
	srand(time(NULL));

	for (int i = 0; i < 50; ++i)
	{
		// Cube Object
		//GameObject* t_CubeObject = new GameObject(Tag("Box", PhysicTag::PHYSICS_KINEMATIC));
		//Transform* t_CubeTransform = new Transform();
		//Render* t_CubeRender = new Render(t_CubeTransform);
		//RigidbodyObject* t_CubeRigidbody = new RigidbodyObject(t_CubeTransform, 1.0f);

		//Vector3 t_Rotation = Vector3(1, 1, 1);
		//Collider* t_CubeCollider = new BoxCollider(t_CubeTransform);

		//// Transform
		//t_CubeObject->SetTransform(t_CubeTransform);
		//t_CubeTransform->SetRotation(t_Rotation);
		//t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);

		//float t_RandX = (rand() % MAX_X) * 2 - (MAX_X / 2);
		//float t_RandY = rand() % MAX_X;
		//float t_RandZ = (rand() % MAX_Z) * 2 - (MAX_Z / 2);

		//t_CubeTransform->SetPosition(t_RandX, 5.0f + t_RandY, t_RandZ);

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

		InsertObjectIntoList(t_CubeObject);
	}
}

SATScreen::~SATScreen()
{
	
}

void SATScreen::ProcessSAT(const float deltaTime, ID3D11Device* device)
{
	// NOTE: Set Game objects to random impulse direction

	if ((GetAsyncKeyState(VK_C) && m_UseOctree == true) & 0x0001) 
	{
		m_UseOctree = false;
	}
	else if ((GetAsyncKeyState(VK_C) && m_UseOctree == false) & 0x0001)
	{
		m_UseOctree = true;
	}
}

void SATScreen::Update(float deltaTime, ID3D11Device* device)
{
	ScreenEntity::Update(deltaTime, device);
	
}

void SATScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	ScreenEntity::Draw(constantBufferData, constBuff, pImmediateContext, device);





}