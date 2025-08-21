#include "BoxCollider.h"
#include "GameObjectEntity.h"

BoxCollider::BoxCollider(Vector3 offset, Vector3 scale)
{
	m_Offset = offset;
	m_Scale = scale;
}

BoxCollider::BoxCollider(Vector3 offset, float width, float height, float length)
{
	m_Offset = offset;
	m_Scale = Vector3(width, height, length);
}

BoxCollider::BoxCollider(Vector3 scale)
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = scale;
}

BoxCollider::BoxCollider(float x_offset, float y_offset, float z_offset, float width, float height, float length)
{
	m_Offset = Vector3(x_offset, y_offset, z_offset);
	m_Scale = Vector3(width, height, length);
}

BoxCollider::BoxCollider()
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = Vector3(1, 1, 1);
}

void BoxCollider::Construct(Vector3 offset, Vector3 scale)
{
	m_Offset = offset;
	m_Scale = scale;
}

void BoxCollider::Construct(Vector3 offset, float width, float height, float length)
{
	m_Offset = offset;
	m_Scale = Vector3(width, height, length);
}

void BoxCollider::Construct(Vector3 scale)
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = scale;
}

void BoxCollider::Construct(float x_offset, float y_offset, float z_offset, float width, float height, float length)
{
	m_Offset = Vector3(x_offset, y_offset, z_offset);
	m_Scale = Vector3(width, height, length);
}

Vector3 BoxCollider::GetMax()
{
	return Vector3(m_Owner->m_Transform.m_Position + m_Offset) + ((m_Owner->m_Transform.m_Scale * m_Scale) / 2);
}

Vector3 BoxCollider::GetMin()
{
	return Vector3(m_Owner->m_Transform.m_Position + m_Offset) - ((m_Owner->m_Transform.m_Scale * m_Scale) / 2);
}
