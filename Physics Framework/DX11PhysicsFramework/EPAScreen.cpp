#include "EPAScreen.h"

EPAScreen::EPAScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_EPA_SCREEN;
	m_GJKCollider = new GJKCollider();
	m_EPACollider = new EPACollider();

	m_Octree = new Octree();
	m_Tree = new Octant();


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

		float t_RandX = rand() % MAX_X - 1;
		float t_RandY = rand() % MAX_X;
		float t_RandZ = rand() % MAX_Z - 1;

		t_CubeTransform->SetPosition(t_RandX, 1.0f, t_RandZ);

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

EPAScreen::~EPAScreen()
{
	Screen::~Screen();
}

void EPAScreen::Update(float deltaTime, ID3D11Device* device)
{
	Screen::Update(deltaTime, device);
	ProcessEPA(deltaTime, device);
}

void EPAScreen::ProcessEPA(const float deltaTime, ID3D11Device* device)
{
	// Collision Manifold
	CollisionManifold t_ColManifold;

	// NOTE: Clear the Octant of Variables
	for (int i = 0; i < 8; ++i) { m_Octree->ClearOctant(m_Tree, i); }

	// NOTE: 
	for (auto& object : m_GameObjects) { m_Octree->InsertEntity(m_Tree, object); }

	// NOTE: Update Tree
	m_Octree->UpdateTree(m_Tree, deltaTime);

	// Query the Tree
	m_Octree->QueryTree(m_Tree);

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
				{
					Timer time;

					// Check the Collision with Code, NOTE: There should be a collision more or less with each other
					if (m_GJKCollider->GJKCollision(t_ObjectAGame->GetCollider(), t_ObjectBGame->GetCollider()) == true)
					{
						// NOTE: Send Simplex Data to the EPA Collision Code
						t_ColManifold = m_EPACollider->EPACollision(m_GJKCollider->GetSimplex(), *t_ObjectAGame->GetCollider(), *t_ObjectBGame->GetCollider());

						if (t_ColManifold.hasCollision == true)
						{
							// NOTE: Material Coef Calculate
							MaterialCoefficient t_MaterialCoef;
							double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
							double t_Rep = 0.5;
							
							// NOTE: Resolve Collision
							Screen::ResolveCollision(t_ObjectARig, t_ObjectBRig, t_Rep, t_ColManifold.collisionNormal);
						}
					}
				}

			}

			// Clear Collision Manifold
			t_ColManifold = CollisionManifold();
		}
	}
}

void EPAScreen::CreatePhysicsObject(ID3D11Device* device)
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

	srand(time(NULL));

	float t_RandX = rand() % 10;
	float t_RandZ = rand() % 10;

	t_CubeTransform->SetPosition(t_RandX, 5.f, t_RandZ);

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
