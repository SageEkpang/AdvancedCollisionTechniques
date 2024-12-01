#pragma once

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// COMPONENT INCLUDE(s)
#include "Transform.h"
#include "Render.h"
#include "PhysicsObject.h"
#include "RigidbodyObject.h"
#include "OBJLoader.h"

using namespace DirectX;

class GameObject
{
private:

	Transform* m_TransformComponent;
	Render* m_RenderComponent;
	PhysicsObject* m_PhysicsComponent;
	RigidbodyObject* m_RigidbodyComponent;

	Tag m_Type;

public:

	// CLASS FUNCTION(s)
	GameObject(Tag type);
	~GameObject();

	Tag GetType() const { return m_Type; }


	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw(ID3D11DeviceContext* pImmediateContext);


	// GETTER FUNCTION(s)
	Transform* GetTransform() { return m_TransformComponent; }
	Render* GetRender() { return m_RenderComponent; }
	PhysicsObject* GetPhysics() { return m_PhysicsComponent; }
	RigidbodyObject* GetRigidbody() { return m_RigidbodyComponent; }


	// SETTER FUNCTION(s)
	void SetTransform(Transform* transform) { m_TransformComponent = transform; }
	void SetRender(Render* render) { m_RenderComponent = render; }
	void SetPhysics(PhysicsObject* physics) { m_PhysicsComponent = physics; }
	void SetRigidbody(RigidbodyObject* rigidbody) { m_RigidbodyComponent = rigidbody; }

	// HELPER FUNCTION()
	HRESULT QuickObject(Vector3 position, Vector3 scale, Vector3 rotation, Collider* collider, char* geoFileName, Material material, const wchar_t* texFileName, ID3D11Device* device);
};

