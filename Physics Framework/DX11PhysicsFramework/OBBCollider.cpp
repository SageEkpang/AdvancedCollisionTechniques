#include "OBBCollider.h"

Vector3 OBBCollider::NearestPoint(Vector3 point)
{
	// TODO: Revise this Function
	// Vector3 t_Result = GetPosition();
	//Vector3 t_Direction = point - GetPosition();

	//for (int i = 0; i < 3; ++i)
	//{
	//	Vector3 t_Axis = m_Orientation; // Testing one Axis at a Time || NOTE: Fills all 3 axis with the same value for the check value, Implement this
	//	float t_Distance = Vector::CalculateDotProduct(t_Direction, t_Axis);

	//	if (t_Distance > m_Size[i]) { t_Distance = m_Size[i]; }
	//	if (t_Distance < -m_Size[i]) { t_Distance = -m_Size[i]; }
	//	t_Result = t_Result + (t_Axis * t_Distance);
	//}

	// return t_Result;
	return Vector3();
}

bool OBBCollider::PointInOBB(Vector3 point)
{
	//Vector3 t_Direction = point - GetPosition();

	//for (int i = 0; i < 3; ++i)
	//{
	//	Vector3 t_Axis = m_Orientation;
	//	float t_Distance = Vector::CalculateDotProduct(t_Direction, t_Axis);

	//	if (t_Distance > m_Size[i])
	//	{
	//		return false;
	//	}

	//	if (t_Distance < -m_Size[i])
	//	{
	//		return false;
	//	}
	//}

	return true;
}
