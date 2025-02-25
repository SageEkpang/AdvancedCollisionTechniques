#include "Screen.h"

Screen::Screen(std::string screenName, ID3D11Device* device)
	: m_ScreenName(screenName)
{
	// Plane Object
	{
		m_GroundPlane = new GameObject(Tag("Plane", PhysicTag::PHYSICS_STATIC));
		Transform* t_PlaneTransform = new Transform();
		Render* t_PlaneRender = new Render(t_PlaneTransform);
		Collider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform);

		float t_BorderLimit = 10000.f;

		// Transform
		m_GroundPlane->SetTransform(t_PlaneTransform);
		t_PlaneTransform->SetScale(t_BorderLimit, 1.0f, t_BorderLimit);

		// Collider
		m_GroundPlane->SetCollider(t_PlaneCollider);

		// Rendering
		m_GroundPlane->SetRender(t_PlaneRender);
		t_PlaneRender->SetGeometryAndMaterial("Resources\\OBJ\\plane.obj", MATERIAL_GROUND, device);
	}
}

Screen::~Screen()
{
	// NOTE: Ground Plane Delete
	delete m_GroundPlane;

	// NOTE: Delete Vector and Objects
	if (!m_GameObjects.empty())
	{
		std::vector<GameObject*>::iterator itr = m_GameObjects.begin();
		for (itr; itr != m_GameObjects.end(); ++itr)
		{
			delete* itr;
		}

		m_GameObjects.clear();
	}
}

void Screen::Update(float deltaTime, ID3D11Device* device)
{
	// NOTE: Ground Plane
	m_GroundPlane->Update(deltaTime);

	if (!m_GameObjects.empty())
	{
		// Updating the Physics Objects
		for (auto& v : m_GameObjects) 
		{ 
			// NOTE: Update Object Regardless of Collision
			v->Update(deltaTime); 

			// NOTE: Check if the Object Has Mass
			if (v->GetRigidbody()->GetMass() == 0) { continue; }

			// NOTE: Apply Gravity to Objects
			v->GetRigidbody()->ApplyImpulse(-v->GetRigidbody()->GetGravity() * deltaTime);

			// NOTE: Resolve Position for the Floor // NOTE: "0" = floor
			if (v->GetTransform()->GetPosition().y - v->GetTransform()->GetScale().y < 0)
			{
				v->GetTransform()->SetPosition(Vector3(v->GetTransform()->GetPosition().x, 0 + v->GetTransform()->GetScale().y, v->GetTransform()->GetPosition().z));
				float t_Dampening = 0.0001f;
				v->GetRigidbody()->SetVelocity(Vector3(v->GetRigidbody()->GetVelocity().x, -v->GetRigidbody()->GetVelocity().y * t_Dampening, v->GetRigidbody()->GetVelocity().z));
			}

			// NOTE: Check Collisions with the Walls, (Left, Right, Back, Front)
			if (v->GetTransform()->GetPosition().x - v->GetTransform()->GetScale().x < MIN_X || v->GetTransform()->GetPosition().x > MAX_X)
			{
				v->GetRigidbody()->ApplyImpulse(Vector3(-v->GetRigidbody()->GetVelocity().x + 1, 0, 0));
			}
			if (v->GetTransform()->GetPosition().z - v->GetTransform()->GetScale().z < MIN_Z || v->GetTransform()->GetPosition().z > MAX_Z)
			{
				v->GetRigidbody()->ApplyImpulse(Vector3(0, 0, -v->GetRigidbody()->GetVelocity().z + 1));
			}
		}
	}
}

void Screen::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (!m_GameObjects.empty())
	{
		for (auto& v : m_GameObjects) { v->Draw(constantBufferData, constBuff, pImmediateContext, device); }
	}
	m_GroundPlane->Draw(constantBufferData, constBuff, pImmediateContext, device);
}

void Screen::InsertObjectIntoList(GameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}
