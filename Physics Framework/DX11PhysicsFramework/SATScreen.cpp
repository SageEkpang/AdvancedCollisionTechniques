#include "SATScreen.h"

SATScreen::SATScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_SAT_SCREEN;

	m_CollisionContact = new CollisionContact();

	// NOTE: Init 100 Objects for Testing Collosions
	srand(time(NULL));

	for (int i = 0; i < 100; ++i)
	{
		Transform* t_Transform = new Transform();

		float t_RandX = rand() % MAX_X - 1;
		float t_RandY = rand() % MAX_X;
		float t_RandZ = rand() % MAX_Z - 1;

		t_Transform->SetPosition(t_RandX, 10.f + t_RandY, t_RandZ);
		t_Transform->SetScale(1.0f, 1.0f, 1.0f);

		SATCollider* t_SatTemp = new SATCollider("Resources\\OBJ\\cube.obj", t_Transform, Vector3(1.0f, 1.0f, 1.0f), 1.0f, device);
		m_SatColliderObjects.push_back(t_SatTemp);
	}
}

SATScreen::~SATScreen()
{
	Screen::~Screen();
}

void SATScreen::ProcessSAT(const float deltaTime, ID3D11Device* device)
{
	// Collision Manifold
	CollisionManifold t_ColManifold;

	// NOTE: Update the Objects and GroundCollision
	for (auto& v : m_SatColliderObjects) 
	{ 
		v->Update(deltaTime); 

		// NOTE: Check if the Object Has Mass
		if (v->GetMass() == 0) { continue; }

		// NOTE: Apply Gravity to Objects
		v->ApplyImpulse(-v->GetGravity() * deltaTime);

		// NOTE: Resolve Position for the Floor // NOTE: "0" = floor
		if (v->GetPosition().y - v->GetScale().y < 0)
		{
			v->SetPosition(Vector3(v->GetPosition().x, 0 + v->GetScale().y, v->GetPosition().z));
			float t_Dampening = 0.01f;
			v->SetVelocity(Vector3(v->GetVelocity().x, -v->GetVelocity().y * t_Dampening, v->GetVelocity().z));
		}

		// NOTE: Check Collisions with the Walls, (Left, Right, Back, Front)
		if (v->GetPosition().x - v->GetScale().x < MIN_X || v->GetPosition().x > MAX_X)
		{
			v->ApplyImpulse(Vector3(-v->GetVelocity().x, 0, 0));
		}
		if (v->GetPosition().z - v->GetScale().z < MIN_Z || v->GetPosition().z > MAX_Z)
		{
			v->ApplyImpulse(Vector3(0, 0, -v->GetVelocity().z));
		}

	}

	// NOTE: Collision Checks
	for (int i = 0; i < m_SatColliderObjects.size(); ++i)
	{
		for (int j = 0; j < m_SatColliderObjects.size(); ++j)
		{
			if (i == j) { continue; }

			// NOTE: Clear Collision Manifold
			t_ColManifold = CollisionManifold();

			// NOTE: SAT Collision Test
			if (SATCollider::ObjectCollisionAlt(*m_SatColliderObjects[i], *m_SatColliderObjects[j], t_ColManifold) == true)
			{
				// Material Coef Calculate
				MaterialCoefficient t_MaterialCoef;
				//double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
				double t_Rep = 0.01;

				ResolveCollision(m_SatColliderObjects[i], m_SatColliderObjects[j], t_Rep, t_ColManifold.collisionNormal);
			}
		}
	}
}

void SATScreen::ResolveCollision(SATCollider* objectA, SATCollider* objectB, float CoefRest, Vector3 normal)
{
	// NOTE: Calculate Impulse to push object out of other object
	Vector3 t_RelativeVelocity = objectA->GetVelocity() - objectB->GetVelocity();
	float t_Impulse = Vector::CalculateDotProduct(t_RelativeVelocity, normal);

	// NOTE: Check if there needs to be a seperation between both of the objects
	if (t_Impulse > 0) { return; }

	float t_E = CoefRest; // Coefficient of Restituion
	float t_Dampening = 0.1f; // Dampening Factor

	// NOTE: Output "Impulse" for result
	float t_J = -(1.0f + t_E) * t_Impulse * t_Dampening;
	objectA->ApplyImpulse(normal * t_J);
	objectB->ApplyImpulse(normal * t_J * -1);
}

void SATScreen::Update(float deltaTime, ID3D11Device* device)
{
	Screen::Update(deltaTime, device);
	ProcessSAT(deltaTime, device);
}

void SATScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	Screen::Draw(constantBufferData, constBuff, pImmediateContext, device);
	for (auto& v : m_SatColliderObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
}
