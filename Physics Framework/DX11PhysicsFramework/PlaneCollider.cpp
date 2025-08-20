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

PlaneCollider::PlaneCollider(float x, float y, float z, float width, float height, float length)
{
	m_Offset = Vector3(x, y, z);
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

void PlaneCollider::Construct(float x, float y, float z, float width, float height, float length)
{
	m_Offset = Vector3(x, y, z);
	m_Scale = Vector3(width, height, length);
}

Vector3 PlaneCollider::NearestPoint(Vector3 point)
{
	float NormalDot = Vector3::S_Dot(m_PlaneNormal, point);
	float t_Distance = NormalDot - Vector3::S_Magnitude(point - m_Owner->m_Transform.m_Position);
	Vector3 ClosestPoint = point - m_PlaneNormal * t_Distance;
	return ClosestPoint;
}

bool PlaneCollider::PointOnPlane(Vector3 point)
{
	float t_Dot = Vector3::S_Dot(point, m_PlaneNormal);
	float t_PlaneDistance = Vector3::S_Magnitude(point - m_Owner->m_Transform.m_Position);
	return t_Dot - t_PlaneDistance == 0.0f;
}
