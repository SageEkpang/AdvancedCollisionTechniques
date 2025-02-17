#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	m_CollisionContact = new CollisionContact();

	#pragma region Donut Object

	// Donut Object
	GameObject* t_DonutObject = new GameObject(Tag("Donut", PhysicTag::PHYSICS_KINEMATIC));
	Transform* t_DonutTransform = new Transform();
	Render* t_DonutRender = new Render(t_DonutTransform);

	RigidbodyObject* t_DonutRigidBody = new RigidbodyObject(t_DonutTransform, 1.0f);
	Collider* t_DonutCollider = new BoxCollider(t_DonutTransform);

	t_DonutObject->SetTransform(t_DonutTransform);
	t_DonutTransform->SetScale(3.0f, 3.0f, 3.0f);
	t_DonutTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_DonutTransform->SetPosition(0.0f, 5.0f, 10.0f);

	t_DonutObject->SetRigidbody(t_DonutRigidBody);
	t_DonutRigidBody->SetCollider(t_DonutCollider);
	t_DonutRigidBody->SetMass(1.0f);
	t_DonutCollider->SetCollisionGeometry("Resources\\CollisionOBJ\\CollisionSphere.obj", MATERIAL_WIREFRAME, device);

	t_DonutObject->SetRender(t_DonutRender);
	t_DonutRender->SetGeometryAndMaterial("Resources\\OBJ\\donut.obj", MATERIAL_SHINY, device);
	t_DonutRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	InsertObjectIntoList(t_DonutObject);

	#pragma endregion

	#pragma region Head Object

	// Head Object
	GameObject* t_HeadObject = new GameObject(Tag("Head", PhysicTag::PHYSICS_KINEMATIC));
	Transform* t_HeadTransform = new Transform();
	Render* t_HeadRender = new Render(t_HeadTransform);
	RigidbodyObject* t_HeadRigidbody = new RigidbodyObject(t_HeadTransform, 0.0f);
	PlaneCollider* t_HeadCollider = new PlaneCollider(t_HeadTransform);

	t_HeadObject->SetTransform(t_HeadTransform);
	t_HeadTransform->SetScale(0.2f, 0.2f, 0.2f);
	t_HeadTransform->SetRotation(0.0f, 180.0f, 0.0f);
	t_HeadTransform->SetPosition(5.0f, 5.0f, 10.0f);

	t_HeadObject->SetRigidbody(t_HeadRigidbody);
	t_HeadRigidbody->SetCollider(t_HeadCollider);

	t_HeadObject->SetRender(t_HeadRender);
	t_HeadRender->SetGeometryAndMaterial("Resources\\OBJ\\joelModel.obj", MATERIAL_SHINY, device);
	t_HeadRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	// InsertObjectIntoList(t_HeadObject);

	#pragma endregion

	#pragma region Spike Ball Object

	// Spike Object
	GameObject* t_SpikeObject = new GameObject(Tag("Spike", PhysicTag::PHYSICS_STATIC));
	Transform* t_SpikeTransform = new Transform();

	Render* t_SpikeRender = new Render(t_SpikeTransform);
	RigidbodyObject* t_SpikeRigidbody = new RigidbodyObject(t_SpikeTransform, 1.0f);
	Collider* t_SpikeCollider = new SphereCollider(t_SpikeTransform, 1.0);

	// Transform
	t_SpikeObject->SetTransform(t_SpikeTransform);
	t_SpikeTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_SpikeTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_SpikeTransform->SetPosition(15.0f, 6.0f, 11.0f);

	// Rigidbody
	t_SpikeObject->SetRigidbody(t_SpikeRigidbody);
	t_SpikeRigidbody->SetMaterial(MaterialTypes::MATERIAL_STAINLESS_STEEL);
	t_SpikeRigidbody->SetCollider(t_SpikeCollider);

	// Collision
	t_SpikeRigidbody->SetCollider(t_SpikeCollider);
	t_SpikeCollider->SetCollisionGeometry("Resources\\OBJ\\CollisionSphere.obj", MATERIAL_WIREFRAME, device);

	// Rendering
	t_SpikeObject->SetRender(t_SpikeRender);
	t_SpikeRender->SetGeometryAndMaterial("Resources\\OBJ\\SpikeBall.obj", MATERIAL_MAX, device);
	t_SpikeRender->SetTexture(L"Resources\\Textures\\stone.dds", device);

	// InsertObjectIntoList(t_SpikeObject);

	#pragma endregion
}

BasicScreen::~BasicScreen()
{
	Screen::~Screen();
}

// TODO: Make this a static function within the Collision contact class with parameters for the intact, can be used for the Octree and Thread Pooling
void BasicScreen::ResolveCollision(const float deltaTime)
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

			Transform* t_ObjectATransform = m_GameObjects[i]->GetTransform();
			Transform* t_ObjectBTransform = m_GameObjects[j]->GetTransform();

			// See if there is a Collider on the rigidbody
			//if (t_ObjectARig->IsCollideable() && t_ObjectBRig->IsCollideable())
			//{
			//	// Check the Collision with Code, NOTE: There should be a collision more or less with each other
			//	if (t_ObjectARig->GetCollider()->CollidesWith(*t_ObjectBRig->GetCollider(), t_ColManifold))
			//	{
			//		// Material Coef Calculate
			//		MaterialCoefficient t_MaterialCoef;
			//		double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
			//		float t_TempRest = 0.2f; // TODO: Change this back to normal restit when the materials are implemented 

			//		// Collision Contact, Resolution, Response and Velocity / Position Resolution
			//		m_CollisionContact->ResolveVelocityAlt(t_ObjectARig, t_ObjectBRig, t_TempRest, deltaTime, t_ColManifold.collisionNormal);
			//		m_CollisionContact->ResolveInterpenetration(t_ObjectAGame, t_ObjectBGame, t_ColManifold.penetrationDepth, t_ColManifold.collisionNormal);
			//	}
			//}

			// Clear Collision Manifold
			t_ColManifold = CollisionManifold();
		}
	}
}

void BasicScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);

	ResolveCollision(deltaTime);
}
