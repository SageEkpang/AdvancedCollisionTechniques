#include "PlaneCollider.h"
#include "GameObjectEntity.h"

PlaneCollider::PlaneCollider(Vector3 offset, Vector3 scale)
{
	m_Offset = offset;
	m_Scale = scale;
}

PlaneCollider::PlaneCollider(Vector3 offset, float width, float height, float length)
{
	m_Offset = offset;
	m_Scale = Vector3(width, height, length);
}

PlaneCollider::PlaneCollider(Vector3 scale)
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = scale;
}

PlaneCollider::PlaneCollider(float x_offset, float y_offset, float z_offset, float width, float height, float length)
{
	m_Offset = Vector3(x_offset, y_offset, z_offset);
	m_Scale = Vector3(width, height, length);
}

PlaneCollider::PlaneCollider()
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = Vector3(1, 1, 1);
}

void PlaneCollider::Construct(Vector3 offset, Vector3 scale)
{
	m_Offset = offset;
	m_Scale = scale;
}

void PlaneCollider::Construct(Vector3 offset, float width, float height, float length)
{
	m_Offset = offset;
	m_Scale = Vector3(width, height, length);
}

void PlaneCollider::Construct(Vector3 scale)
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = scale;
}

void PlaneCollider::Construct(float x_offset, float y_offset, float z_offset, float width, float height, float length)
{
	m_Offset = Vector3(x_offset, y_offset, z_offset);
	m_Scale = Vector3(width, height, length);
}

Vector3 PlaneCollider::GetMax()
{
	return (m_Owner->m_Transform.m_Position + m_Offset) + ((m_Owner->m_Transform.m_Scale * m_Scale) / 2);
}

Vector3 PlaneCollider::GetMin()
{
	return (m_Owner->m_Transform.m_Position + m_Offset) - ((m_Owner->m_Transform.m_Scale * m_Scale) / 2);
}