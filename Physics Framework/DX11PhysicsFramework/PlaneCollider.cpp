#include "PlaneCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

bool PlaneCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{
	return false;

	// Plane Component Variables
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
		out.collisionNormal = GetPlaneNormal();
		return true;
	}

	return false;
}

bool PlaneCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
	Vector3 ClosestPoint = NearestPoint(other.GetPosition());
	float Distance = Vector::Magnitude(Vector::DistanceTo(ClosestPoint, other.GetPosition()));

	if (Distance <= other.GetRadius())
	{
		out.collisionNormal = GetPlaneNormal();
		return true;
	}

	return false;
}

bool PlaneCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
	Vector3 ClosestPoint = NearestPoint(other.GetPosition());

	// Box Component Variables
	// Centre Position (-+) Extents
	m_Max = other.GetPosition() + other.GetScale();
	m_Min = other.GetPosition() - other.GetScale();

	if (ClosestPoint.x < m_Min.x || ClosestPoint.x > m_Max.x) return false;
	if (ClosestPoint.y < m_Min.y || ClosestPoint.y > m_Max.y) return false;
	if (ClosestPoint.z < m_Min.z || ClosestPoint.z > m_Max.z) return false;

	out.collisionNormal = GetPlaneNormal();
	return true;
}

Vector3 PlaneCollider::NearestPoint(Vector3 point)
{
	Vector3 PlaneNormal = Vector3(0, 1, 0);
	float NormalDot = Vector::CalculateDotProductNotNorm(PlaneNormal, point);
	float t_Distance = NormalDot - Vector::Magnitude(point - m_Transform->GetPosition());
	Vector3 ClosestPoint = point - PlaneNormal * t_Distance;
	return ClosestPoint;

	// Ax + By + Cz = d
	// <a, b, c> = n
	// Unit Vector
}