#include "SATScreen.h"

SATScreen::SATScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_SAT_SCREEN;

	m_CollisionContact = new CollisionContact();

	#pragma region PlaneObject

	// Plane Object
	{
		GameObject* t_PlaneObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_STATIC));
		Transform* t_PlaneTransform = new Transform();
		Render* t_PlaneRender = new Render(t_PlaneTransform);
		RigidbodyObject* t_PlaneRigidbody = new RigidbodyObject(t_PlaneTransform, 0.0f);
		// Collider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform); // FIXME: Planar Collisions Tweaking Out
		Collider* t_PlaneCollider = new SphereCollider(t_PlaneTransform, 1.0);

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

	#pragma region Cube1

	{
		// Cube Object
		GameObject* t_CubeObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_KINEMATIC));
		Transform* t_CubeTransform = new Transform();
		Render* t_CubeRender = new Render(t_CubeTransform);
		RigidbodyObject* t_CubeRigidbody = new RigidbodyObject(t_CubeTransform, 1.0f);
		// Collider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform); // FIXME: Planar Collisions Tweaking Out
	
		Vector3 t_Rotation = Vector3(0, 0, 0);
		Collider* t_CubeCollider = new OBBCollider(t_CubeTransform, t_Rotation);

		// Transform
		t_CubeObject->SetTransform(t_CubeTransform);
		t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);
		t_CubeTransform->SetRotation(t_Rotation);
		t_CubeTransform->SetPosition(0.0f, 5.0f, 10.0f);

		// Rigidbody 
		t_CubeObject->SetRigidbody(t_CubeRigidbody);
		t_CubeRigidbody->SetMaterial(MaterialTypes::MATERIAL_SILICON);
		t_CubeRigidbody->SetCollider(t_CubeCollider);

		// Collision
		t_CubeObject->SetCollider(t_CubeCollider);
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
		GameObject* t_CubeObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_KINEMATIC));
		Transform* t_CubeTransform = new Transform();
		Render* t_CubeRender = new Render(t_CubeTransform);
		RigidbodyObject* t_CubeRigidbody = new RigidbodyObject(t_CubeTransform, 1.0f);

		Vector3 t_Rotation = Vector3(0, 0, 0);
		Collider* t_CubeCollider = new OBBCollider(t_CubeTransform, t_Rotation);

		// Transform
		t_CubeObject->SetTransform(t_CubeTransform);
		t_CubeTransform->SetScale(1.0f, 1.0f, 1.0f);
		t_CubeTransform->SetRotation(t_Rotation);
		t_CubeTransform->SetPosition(3.0f, 5.0f, 10.0f);

		// Rigidbody 
		t_CubeObject->SetRigidbody(t_CubeRigidbody);
		t_CubeRigidbody->SetMaterial(MaterialTypes::MATERIAL_SILICON);
		t_CubeRigidbody->SetCollider(t_CubeCollider);

		// Collision
		t_CubeObject->SetCollider(t_CubeCollider);
		// t_CubeCollider->SetCollisionGeometry("Resources\\OBJ\\CollisionCube.obj", MATERIAL_WIREFRAME, device);

		// Rendering
		t_CubeObject->SetRender(t_CubeRender);
		t_CubeRender->SetGeometryAndMaterial("Resources\\OBJ\\cube.obj", MATERIAL_SHINY, device);
		t_CubeRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

		InsertObjectIntoList(t_CubeObject);
	}
	#pragma endregion


}

SATScreen::~SATScreen()
{
	Screen::~Screen();
}

void SATScreen::ResolveCollision(const float deltaTime)
{
	// Collision Manifold
	CollisionManifold t_ColManifold;

	// m_GameObjects[1]->GetRigidbody()->AddForce(Vector3(1, 0, 0));
	m_GameObjects[2]->GetRigidbody()->AddForce(Vector3(-1.0, 0, 0));

	// static int rot;
	// rot += 100 * deltaTime;
	// m_GameObjects[1]->GetTransform()->SetRotation(0, rot / 2, 0);
	// m_GameObjects[2]->GetTransform()->SetRotation(0, rot, 0);

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

			Transform* t_ObjectATransform = m_GameObjects[i]->GetTransform();
			Transform* t_ObjectBTransform = m_GameObjects[j]->GetTransform();

			// See if there is a Collider on the rigidbody
			if (t_ObjectARig->IsCollideable() && t_ObjectBRig->IsCollideable())
			{
				// Check the Collision with Code, NOTE: There should be a collision more or less with each other
				if (t_ObjectARig->GetCollider()->CollidesWith(*t_ObjectBRig->GetCollider(), t_ColManifold))
				{
					//// Material Coef Calculate
					// MaterialCoefficient t_MaterialCoef;
					//double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
					//float t_TempRest = 0.00001f; // TODO: Change this back to normal restit when the materials are implemented 

					//// Collision Contact, Resolution, Response and Velocity / Position Resolution
					//// CollisionContact t_CollisionContact;
					//m_CollisionContact->ResolveVelocityAlt(t_ObjectARig, t_ObjectBRig, t_TempRest, deltaTime, t_ColManifold.collisionNormal);
					//m_CollisionContact->ResolveInterpenetration(t_ObjectAGame, t_ObjectBGame, t_ColManifold.penetrationDepth, t_ColManifold.collisionNormal);
				}

				if (SATCollider::ObjectCollision((OBBCollider*)t_ObjectAGame->GetCollider(), (OBBCollider*)t_ObjectBGame->GetCollider(), t_ColManifold))
				{
					int i = 0;
				}

			}

			// Clear Collision Manifold
			t_ColManifold = CollisionManifold();
		}
	}
}

void SATScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
	ResolveCollision(deltaTime);
}
