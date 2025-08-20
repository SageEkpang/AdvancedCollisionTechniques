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

Vector3 BoxCollider::NearestPoint(Vector3 point)
{
	// Min and Max Extents of Box Collider
	const Vector3 t_Max = (m_Owner->m_Transform.m_Position + m_Offset) + (m_Scale);
	const Vector3 t_Min = (m_Owner->m_Transform.m_Position + m_Offset) - (m_Scale);

	// Calculating the nearest point
	float t_NearPointX = (point.x < t_Min.x) ? t_Min.x : point.x;
	float t_NearPointY = (point.y < t_Min.y) ? t_Min.y : point.y;
	float t_NearPointZ = (point.z < t_Min.z) ? t_Min.z : point.z;

	// If the nearest point on the axis (x, y, z) are more than the extents, assign the max extent
	t_NearPointX = (t_NearPointX > t_Max.x) ? t_Max.x : t_NearPointX;
	t_NearPointY = (t_NearPointY > t_Max.y) ? t_Max.y : t_NearPointY;
	t_NearPointZ = (t_NearPointZ > t_Max.z) ? t_Max.z : t_NearPointZ;

	// Return final computed video
	return Vector3(t_NearPointX, t_NearPointY, t_NearPointZ);
}

bool BoxCollider::PointInBox(Vector3 point)
{
	const Vector3 t_Max = (m_Owner->m_Transform.m_Position + m_Offset) + (m_Scale);
	const Vector3 t_Min = (m_Owner->m_Transform.m_Position + m_Offset) - (m_Scale);
	
	// Not in Box
	if (point.x < t_Min.x || point.y < t_Min.y || point.z < t_Min.z) { return false; }
	if (point.x > t_Max.x || point.y > t_Max.y || point.z > t_Max.z) { return false; }

	// In Box
	return true;
}
