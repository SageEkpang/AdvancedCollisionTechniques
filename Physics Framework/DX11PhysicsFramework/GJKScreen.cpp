#include "GJKScreen.h"

GJKScreen::GJKScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_GJK_SCREEN;

	m_GJKCollider = new GJKCollider();

	// NOTE: Octree Init
	m_Octree = new Octree(Vector3(10, 10, 10), 60, 3);

	srand(time(NULL));
	for (int i = 0; i < 50; ++i)
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
		t_CubeTransform->SetRotation(t_Rotation);
		t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);

		float t_RandX = (rand() % MAX_X) * 2 - (MAX_X / 2) - 10;
		float t_RandY = rand() % MAX_X;
		float t_RandZ = (rand() % MAX_Z) * 2 - (MAX_Z / 2) - 10;

		t_CubeTransform->SetPosition(t_RandX, 10.0f + t_RandY, t_RandZ);

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
}

GJKScreen::~GJKScreen()
{
	Screen::~Screen();
}

void GJKScreen::Update(float deltaTime, ID3D11Device* device)
{
	Screen::Update(deltaTime, device);
	ProcessGJK(deltaTime);
}

void GJKScreen::RandomImpulseDirection(float deltaTime)
{
	for (auto& v : m_GameObjects)
	{
		float t_RandX = (rand() % 10) * 2 - 10;
		float t_RandY = rand() % 3;
		float t_RandZ = (rand() % 10) * 2 - 10;

		v->GetRigidbody()->ApplyImpulse(Vector3(t_RandX, t_RandY, t_RandZ));
	}
}

void GJKScreen::ProcessGJK(const float deltaTime)
{
	if (GetAsyncKeyState(VK_RETURN)) { RandomImpulseDirection(deltaTime); }

	if ((GetAsyncKeyState(VK_C) && m_UseOctree == true) & 0x0001)
	{
		m_UseOctree = false;
	}
	else if ((GetAsyncKeyState(VK_C) && m_UseOctree == false) & 0x0001)
	{
		m_UseOctree = true;
	}

	if (m_UseOctree == true)
	{
		// NOTE: Clear Octree of Values
		for (int i = 0; i < 8; ++i) { m_Octree->ClearTree(i); }

		// NOTE: Insert Entities
		for (auto& v : m_GameObjects) { m_Octree->InsertEntity(v); }

		// NOTE: Update the Tree
		m_Octree->UpdateTree(deltaTime);

		// NOTE: Query Tree
		m_Octree->QueryTree(GJKCollider::S_GJKCollision, CollisionContact::S_ResolveInterpenetration);
	}
	else if (m_UseOctree == false)
	{
		// Collision Checks
		for (int i = 0; i < m_GameObjects.size(); ++i)
		{
			for (int j = 0; j < m_GameObjects.size(); ++j)
			{
				// Do not do the Same Game Object
				if (i == j) { continue; }

				// Get Rigidbody Information from the Objects (Objects Colliding with Each Other)
				GameObject* t_ObjectAGame = m_GameObjects[i];
				GameObject* t_ObjectBGame = m_GameObjects[j];

				RigidbodyObject* t_ObjectARig = m_GameObjects[i]->GetRigidbody();
				RigidbodyObject* t_ObjectBRig = m_GameObjects[j]->GetRigidbody();

				// See if there is a Collider on the rigidbody
				if (t_ObjectARig->IsCollideable() && t_ObjectBRig->IsCollideable())
				{
					// NOTE: Calculation of GJK Collider
					CollisionManifold t_ColManifold = m_GJKCollider->GJKCollision(t_ObjectAGame->GetCollider(), t_ObjectBGame->GetCollider());

					// Check the Collision with Code, NOTE: There should be a collision more or less with each other
					if (t_ColManifold.hasCollision == true)
					{
						// NOTE: Material Coef Calculation
						MaterialCoefficient t_MaterialCoef;
						// double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
						double t_Rep = 0.0001;

						// NOTE: Resolve Collision
						CollisionContact t_ColContact;
						t_ColContact.ResolveVelocityAlt(t_ObjectARig, t_ObjectBRig, 0.001, deltaTime, t_ColManifold.collisionNormal);
						t_ColContact.ResolveInterpenetration(t_ObjectAGame, t_ObjectBGame, 1, t_ColManifold.collisionNormal);
					}
				}
			}
		}
	}
}
