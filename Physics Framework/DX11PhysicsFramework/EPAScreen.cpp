#include "EPAScreen.h"

EPAScreen::EPAScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_EPA_SCREEN;
	m_GJKCollider = new GJKCollider();
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
		t_CubeTransform->SetPosition(10.0f, 10.0f, 10.0f);

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
		t_CubeTransform->SetPosition(9.f, 5.f, 9.0f);

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
	ProcessEPA(deltaTime);
}

void EPAScreen::ProcessEPA(const float deltaTime)
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
				// Check the Collision with Code, NOTE: There should be a collision more or less with each other
				if (m_GJKCollider->GJKCollision(t_ObjectAGame->GetCollider(), t_ObjectBGame->GetCollider()))
				{
					// NOTE: Send Simplex Data to the EPA Collision Code
					t_ColManifold = m_EPACollider->EPACollision(m_GJKCollider->GetSimplex(), *t_ObjectAGame->GetCollider(), *t_ObjectBGame->GetCollider());

					if (t_ColManifold.hasCollision == true)
					{
						// Material Coef Calculate
						MaterialCoefficient t_MaterialCoef;
						double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
						double t_Rep = 1;

						// NOTE: Resolve Collision
						ResolveCollision(t_ObjectARig, t_ObjectBRig, t_Rep, t_ColManifold.collisionNormal);
					}
				}


				//// Collision Contact, Resolution, Response and Velocity / Position Resolution
				//// CollisionContact t_CollisionContact;
				//m_CollisionContact->ResolveVelocityAlt(t_ObjectARig, t_ObjectBRig, t_TempRest, deltaTime, t_ColManifold.collisionNormal);
				//m_CollisionContact->ResolveInterpenetration(t_ObjectAGame, t_ObjectBGame, t_ColManifold.penetrationDepth, t_ColManifold.collisionNormal);
			}

			// Clear Collision Manifold
			t_ColManifold = CollisionManifold();
		}
	}
}

void EPAScreen::ResolveCollision(RigidbodyObject* objectA, RigidbodyObject* objectB, float CoefRest, Vector3 normal)
{
	// NOTE: Calculate Impulse to push object out of other object
	Vector3 t_RelativeVelocity = objectA->GetVelocity() - objectB->GetVelocity();
	float t_Impulse = Vector::CalculateDotProductNotNorm(t_RelativeVelocity, normal);

	// NOTE: Check if there needs to be a seperation between both of the objects
	if (t_Impulse > 0) { return; }

	float t_E = CoefRest; // Coefficient of Restituion
	float t_Dampening = 1.f; // Dampening Factor

	// NOTE: Output "Impulse" for result
	float t_J = -(1.0f + t_E) * t_Impulse * t_Dampening;
	objectA->ApplyImpulse(normal * t_J);
	objectA->ApplyImpulse(normal * t_J);
}
