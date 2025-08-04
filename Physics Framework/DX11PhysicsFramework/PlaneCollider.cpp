#include "PlaneCollider.h"

Vector3 PlaneCollider::NearestPoint(Vector3 point)
{
	/*float NormalDot = Vector::CalculateDotProductNotNorm(m_PlaneNormal, point);
	float t_Distance = NormalDot - Vector::Magnitude(point - m_Transform->GetPosition());
	Vector3 ClosestPoint = point - m_PlaneNormal * t_Distance;
	return ClosestPoint;*/
	return Vector3();
}

bool PlaneCollider::PointOnPlane(Vector3 point)
{
	/*float t_Dot = Vector::CalculateDotProduct(point, m_PlaneNormal);
	float t_PlaneDistance = Vector::Magnitude(point - m_Transform->GetPosition());
	return t_Dot - t_PlaneDistance == 0.0f;*/
	return true;
}
