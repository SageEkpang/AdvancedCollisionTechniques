#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "OBBCollider.h"
#include "SATCollider.h"

bool BoxCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	// Box Component Variables
	// Centre Position (-+) Extents
	m_Max = GetPosition() + GetScale();
	m_Min = GetPosition() - GetScale();

	// Other Object Min and Max Values
	// Centre Position (-+) Extents
	Vector3 OtherMax = other.GetPosition() + other.GetScale();
	Vector3 OtherMin = other.GetPosition() - other.GetScale();

	if (m_Min.x <= OtherMax.x &&
		m_Max.x >= OtherMin.x &&

		m_Min.y <= OtherMax.y &&
		m_Max.y >= OtherMin.y &&

		m_Min.z <= OtherMax.z &&
		m_Max.z >= OtherMin.z)
	{
		out.collisionNormal = Vector::Normalise(GetPosition() - other.GetPosition());
		out.contactPointCount = 1;
		out.hasCollision = true;
		out.penetrationDepth = fabs(Vector::Magnitude(GetPosition() - other.GetPosition()));

		return true;
	}

	return false;
}

bool BoxCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	// Sphere Component Variables
	Vector3 TempPos = other.GetPosition();
	float TempRadius = other.GetRadius();

	// Box Component Variables
	// Centre Position (-+) Extents
	m_Max = GetPosition() + GetScale();
	m_Min = GetPosition() - GetScale();

	// Minimum Distance Temp Variable
	float DistanceMin = 0;

	// Check the Distance of the Circle Position from the Box position and extents
	if (TempPos.x < m_Min.x) DistanceMin += std::powf(TempPos.x - m_Min.x, 2);
	else if (TempPos.x > m_Max.x) DistanceMin += std::powf(TempPos.x - m_Max.x, 2);

	if (TempPos.y < m_Min.y) DistanceMin += std::powf(TempPos.y - m_Min.y, 2);
	else if (TempPos.y > m_Max.y) DistanceMin += std::powf(TempPos.y - m_Max.y, 2);

	if (TempPos.z < m_Min.z) DistanceMin += std::powf(TempPos.z - m_Min.z, 2);
	else if (TempPos.z > m_Max.z) DistanceMin += std::powf(TempPos.z - m_Max.z, 2);

	// Check if the Distance of the Circle is in the Box's "Radius"
	if (DistanceMin <= (std::powf(TempRadius, 2)))
	{
		out.collisionNormal = Vector::Normalise(other.GetPosition() - GetPosition());
		out.collisionNormal = Vector::Normalise(out.collisionNormal);
		out.hasCollision = true;
		out.points[0].position = GetPosition() + (out.collisionNormal * GetRadius());

		int t_AverageScale = abs(GetScale().x + GetScale().y + GetScale().z / 3);
		out.penetrationDepth = fabs(Vector::Magnitude(other.GetPosition() - GetPosition()) - t_AverageScale);
		return true;
	}

	return false;
}

bool BoxCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{
	Vector3 ClosestPoint = other.NearestPoint(GetPosition());

	m_Max = GetPosition() + GetScale();
	m_Min = GetPosition() - GetScale();

	float t_Length = GetScale().x * fabsf(other.GetPlaneNormal().x) +
					 GetScale().y * fabsf(other.GetPlaneNormal().y) +
					 GetScale().z * fabsf(other.GetPlaneNormal().z);

	float t_NormalDot = Vector::CalculateDotProductNotNorm(other.GetPlaneNormal(), GetPosition());
	float t_Distance = t_NormalDot - Vector::Magnitude(Vector::DistanceTo(other.GetPosition(), GetPosition()));
	return fabsf(t_Distance) <= t_Length;
}

bool BoxCollider::CollidesWith(OBBCollider& other, CollisionManifold& out)
{
	
	return false;
}

Vector3 BoxCollider::NearestPoint(Vector3 point)
{
	// Min and Max Extents of Box Collider
	m_Max = GetPosition() + GetScale();
	m_Min = GetPosition() - GetScale();

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
