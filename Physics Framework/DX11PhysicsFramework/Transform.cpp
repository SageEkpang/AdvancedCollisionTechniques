#include "Transform.h"

Transform::Transform()
{
	m_Parent = nullptr;
	m_World = new XMFLOAT4X4();

	m_Position = Vector3(0, 0, 0);
	m_Scale = Vector3(1, 1, 1);
	m_Orientation = Quaternion4(0, 0, 0, 1);
}

Transform::~Transform()
{
	if (m_World != nullptr) { delete m_World; }
	if (m_Parent != nullptr) { delete m_Parent; }

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
	DirectX::XMStoreFloat4x4(m_World, Scale * Orientation * Position);

	// Set Parent
	if (m_Parent != nullptr)
	{
		DirectX::XMStoreFloat4x4(m_World, this->GetWorldMatrix() * m_Parent->GetWorldMatrix());
	}
}