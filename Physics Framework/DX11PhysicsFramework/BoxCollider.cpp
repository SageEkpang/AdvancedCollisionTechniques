#include "BoxCollider.h"

Vector3 BoxCollider::NearestPoint(Vector3 point)
{
	// Min and Max Extents of Box Collider
	//m_Max = GetPosition() + GetScale();
	//m_Min = GetPosition() - GetScale();

	// Calculating the nearest point
	float t_NearPointX = (point.x < m_Min.x) ? m_Min.x : point.x;
	float t_NearPointY = (point.y < m_Min.y) ? m_Min.y : point.y;
	float t_NearPointZ = (point.z < m_Min.z) ? m_Min.z : point.z;

	// If the nearest point on the axis (x, y, z) are more than the extents, assign the max extent
	t_NearPointX = (t_NearPointX > m_Max.x) ? m_Max.x : t_NearPointX;
	t_NearPointY = (t_NearPointY > m_Max.y) ? m_Max.y : t_NearPointY;
	t_NearPointZ = (t_NearPointZ > m_Max.z) ? m_Max.z : t_NearPointZ;

	// Return final computed video
	return Vector3(t_NearPointX, t_NearPointY, t_NearPointZ);
}

bool BoxCollider::PointInBox(Vector3 point)
{
	Vector3 t_Min = m_Min; // Might Not Work
	Vector3 t_Max = m_Max;
	
	// Not in Box
	if (point.x < t_Min.x || point.y < t_Min.y || point.z < t_Min.z) { return false; }
	if (point.x > t_Max.x || point.y > t_Max.y || point.z > t_Max.z) { return false; }

	// In Box
	return true;
}
