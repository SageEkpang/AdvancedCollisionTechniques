#include "Transform.h"

Transform::Transform()
{
	m_Parent = nullptr;
	m_World = new XMFLOAT4X4();

	m_Position = Vector3();
	m_Scale = Vector3();
	m_Orientation = Quaternion4();
}

Transform::~Transform()
{
	if (m_World != nullptr)
	{
		delete m_World;
		// m_World = nullptr;
	}

	if (m_Parent != nullptr)
	{
		delete m_Parent;
		// m_Parent = nullptr;
	}
}

void Transform::Update(float DeltaTime)
{
	// Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	// Rotation Matrix
	XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(m_Orientation.x, m_Orientation.y, m_Orientation.z, m_Orientation.w));

	// Position Matrix
	XMMATRIX Position = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, Scale * Orientation * Position);

	// Set Parent
	if (m_Parent != nullptr)
	{
		XMStoreFloat4x4(m_World, this->GetWorldMatrix() * m_Parent->GetWorldMatrix());
	}
}

void Transform::Move(Vector3 Direction)
{
	m_Position += Direction;
}

void Transform::Resize(Vector3 Direction)
{
	m_Scale += Direction;
}
