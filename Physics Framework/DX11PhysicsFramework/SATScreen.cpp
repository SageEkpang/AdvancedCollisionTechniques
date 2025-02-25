#include "SATScreen.h"

SATScreen::SATScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_SAT_SCREEN;

	// NOTE: Init SAT
	m_SatCollider = new SATCollider();

	// NOTE: Octree Init
	m_Octree = new Octree(Vector3(10, 10, 10), 60, 3);

	// NOTE: Init 50 Objects for Testing Collosions
	srand(time(NULL));

	for (int i = 0; i < 50; ++i)
	{
		// Cube Object
		GameObject* t_CubeObject = new GameObject(Tag("Box", PhysicTag::PHYSICS_KINEMATIC));
		Transform* t_CubeTransform = new Transform();
		Render* t_CubeRender = new Render(t_CubeTransform);
		RigidbodyObject* t_CubeRigidbody = new RigidbodyObject(t_CubeTransform, 1.0f);

		Vector3 t_Rotation = Vector3(1, 1, 1);
		Collider* t_CubeCollider = new BoxCollider(t_CubeTransform);

		// Transform
		t_CubeObject->SetTransform(t_CubeTransform);
		t_CubeTransform->SetRotation(t_Rotation);
		t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);

		float t_RandX = (rand() % MAX_X) * 2 - (MAX_X / 2);
		float t_RandY = rand() % MAX_X;
		float t_RandZ = (rand() % MAX_Z) * 2 - (MAX_Z / 2);

		t_CubeTransform->SetPosition(t_RandX, 5.0f + t_RandY, t_RandZ);

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

SATScreen::~SATScreen()
{
	Screen::~Screen();
}

void SATScreen::ProcessSAT(const float deltaTime, ID3D11Device* device)
{
	// NOTE: Set Game objects to random impulse direction
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

		// NOTE: Query the Different parts of the Tree
		m_Octree->QueryTree(SATCollider::S_SATCollision, CollisionContact::S_ResolveInterpenetration);
	}
	else if (m_UseOctree == false)
	{
		// NOTE: Collision Checks
		for (int i = 0; i < m_GameObjects.size(); ++i)
		{
			for (int j = 0; j < m_GameObjects.size(); ++j)
			{
				if (i == j) { continue; }

				// Get Rigidbody Information from the Objects (Objects Colliding with Each Other)
				GameObject* t_ObjectAGame = m_GameObjects[i];
				GameObject* t_ObjectBGame = m_GameObjects[j];

				RigidbodyObject* t_ObjectARig = m_GameObjects[i]->GetRigidbody();
				RigidbodyObject* t_ObjectBRig = m_GameObjects[j]->GetRigidbody();

				// NOTE: Clear Collision Manifold
				CollisionManifold t_ColManifold = m_SatCollider->SATCollision(*m_GameObjects[i], *m_GameObjects[j]);

				// NOTE: SAT Collision Test
				if (t_ColManifold.hasCollision == true)
				{
					// Material Coef Calculate
					MaterialCoefficient t_MaterialCoef;
					//double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
					double t_Rep = 0.1;

					CollisionContact t_ColContact;
					t_ColContact.ResolveVelocityAlt(t_ObjectARig, t_ObjectBRig, 0.1, deltaTime, t_ColManifold.collisionNormal);
					t_ColContact.ResolveInterpenetration(t_ObjectAGame, t_ObjectBGame, 0.1, t_ColManifold.collisionNormal);
				}
			}
		}
	}
}

void SATScreen::Update(float deltaTime, ID3D11Device* device)
{
	Screen::Update(deltaTime, device);
	ProcessSAT(deltaTime, device);
}

void SATScreen::RandomImpulseDirection(float deltaTime)
{
	for (auto& v : m_GameObjects)
	{
		float t_RandX = (rand() % 10) * 2 - 10;
		float t_RandY = rand() % 3;
		float t_RandZ = (rand() % 10) * 2 - 10;

		v->GetRigidbody()->ApplyImpulse(Vector3(t_RandX, t_RandY, t_RandZ));
	}
}