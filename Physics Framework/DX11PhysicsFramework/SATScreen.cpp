#include "SATScreen.h"

SATScreen::SATScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_SAT_SCREEN;

	m_CollisionContact = new CollisionContact();

	// NOTE: Object A
	{
		Transform* t_TransformA = new Transform();

		t_TransformA->SetPosition(1.0f, 1.0f, 10.0f);
		t_TransformA->SetScale(1.0f, 1.0f, 1.0f);

		SATCollider* t_SatCol = new SATCollider("Resources\\OBJ\\cube.obj", t_TransformA, Vector3(1.0f, 1.0f, 1.0f), 1.0f, device);
		m_SatColliderObjects.push_back(t_SatCol);
	}

	// NOTE: Object B
	{
		Transform* t_TransformB = new Transform();

		t_TransformB->SetPosition(3.5f, 1.0f, 10.0f);
		t_TransformB->SetScale(1.0f, 1.0f, 1.0f);

		SATCollider* t_SatCol2 = new SATCollider("Resources\\OBJ\\cube.obj", t_TransformB, Vector3(1.0f, 1.0f, 1.0f), 1.0f, device);
		m_SatColliderObjects.push_back(t_SatCol2);
	}
}

SATScreen::~SATScreen()
{
	Screen::~Screen();
}

void SATScreen::ResolveCollision(SATCollider* objectA, SATCollider* objectB, float CoefResat, Vector3 normal)
{
}

void SATScreen::ProcessSAT(const float deltaTime)
{
	// Collision Manifold
	CollisionManifold t_ColManifold;

	for (auto& v : m_SatColliderObjects) { v->Update(deltaTime); }

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
				double t_RestCoef = t_MaterialCoef.MaterialRestCoef(m_GameObjects[i]->GetRigidbody()->GetMaterial(), m_GameObjects[j]->GetRigidbody()->GetMaterial());
				double t_Rep = 0.01;

				ResolveCollision(m_SatColliderObjects[i], m_SatColliderObjects[j], t_Rep, t_ColManifold.collisionNormal);
			}
		}
	}
}

void SATScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
	ProcessSAT(deltaTime);
}

void SATScreen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	Screen::Draw(constantBufferData, constBuff, pImmediateContext, device);
	for (auto& v : m_SatColliderObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
}
