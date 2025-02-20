#include "GJKScreen.h"

GJKScreen::GJKScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_GJK_SCREEN;

	m_GJKCollider = new GJKCollider();

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

		float t_RandX = rand() % MAX_X - 1;
		float t_RandY = rand() % MAX_X;
		float t_RandZ = rand() % MAX_Z - 1;

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

void GJKScreen::ResolveCollision(RigidbodyObject* objectA, RigidbodyObject* objectB, float CoefRest, Vector3 normal)
{
	// NOTE: Calculate Impulse to push object out of other object
	Vector3 t_RelativeVelocity = objectA->GetVelocity() - objectB->GetVelocity();
	float t_Impulse = Vector::CalculateDotProduct(t_RelativeVelocity, normal);

	// NOTE: Check if there needs to be a seperation between both of the objects
	if (t_Impulse > 0) { return; }

	float t_E = CoefRest; // Coefficient of Restituion
	float t_Dampening = 1.f; // Dampening Factor

	// NOTE: Output "Impulse" for result
	float t_J = -(1.0f + t_E) * t_Impulse * t_Dampening;
	objectA->ApplyImpulse(normal * t_J);
	objectB->ApplyImpulse(normal * t_J * -1);
}

void GJKScreen::ProcessGJK(const float deltaTime)
{
	// Collision Manifold
	CollisionManifold t_ColManifold;

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
						// NOTE: Material Coef Calculation
						MaterialCoefficient t_MaterialCoef;
						double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
						double t_Rep = 0.01;

						// NOTE: Resolve Collision
						t_ColManifold.penetrationDepth = 1.0;
						t_ColManifold.collisionNormal = t_ObjectAGame->GetTransform()->GetPosition() - t_ObjectBGame->GetTransform()->GetPosition();
						ResolveCollision(t_ObjectARig, t_ObjectBRig, t_Rep, t_ColManifold.collisionNormal);
					}
				}
			}

			// Clear Collision Manifold
			t_ColManifold = CollisionManifold();
		}
	}
}

