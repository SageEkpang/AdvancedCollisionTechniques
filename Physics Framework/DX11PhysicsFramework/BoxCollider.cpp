#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

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
		out.collisionNormal = Vector::Normalise(other.GetPosition() - GetPosition());
		out.contactPointCount = 8;
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
		return true;
	}

	return false;
}

bool BoxCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{
	Vector3 ClosestPoint = other.NearestPoint(GetPosition());


	m_Max = GetPosition() + GetScale();
	m_Min = GetPosition() - GetScale();

	if (ClosestPoint.x < m_Min.x || ClosestPoint.x > m_Max.x) return false;
	if (ClosestPoint.y < m_Min.y || ClosestPoint.y > m_Max.y) return false;
	if (ClosestPoint.z < m_Min.z || ClosestPoint.z > m_Max.z) return false;

	out.collisionNormal = other.GetPlaneNormal();

	return true;
}

Vector3 BoxCollider::NearestPoint(Vector3 point)
{
	// Min and Max Extents of Box Collider
	m_Max = GetPosition() + GetScale();
	m_Min = GetPosition() - GetScale();

	// Calculating the nearest point
	float xx = (point.x < m_Min.x) ? m_Min.x : point.x;
	float yy = (point.y < m_Min.y) ? m_Min.y : point.y;
	float zz = (point.z < m_Min.z) ? m_Min.z : point.z;

	// If the nearest point on the axis (x, y, z) are more than the extents, assign the max extent
	xx = (xx > m_Max.x) ? m_Max.x : xx;
	yy = (yy > m_Max.y) ? m_Max.y : yy;
	zz = (zz > m_Max.z) ? m_Max.z : zz;

	// Return final computed vide
	return Vector3(xx, yy, zz);
}