#include "OBBCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "SATCollider.h"

bool OBBCollider::CollidesWith(OBBCollider& other, CollisionManifold& out)
{
	float t_RA, t_RB;
	XMFLOAT3X3 t_R, t_AbsR;

	m_Extents[0] = GetScale().x / 2;
	m_Extents[1] = GetScale().y / 2;
	m_Extents[2] = GetScale().z / 2;

	other.m_Extents[0] = other.GetTransform()->GetScale().x;
	other.m_Extents[1] = other.GetTransform()->GetScale().y;
	other.m_Extents[2] = other.GetTransform()->GetScale().z;

	Vector3 t_Test1[3] = {

		Vector3(GetRotation().x, 0, 0),
		Vector3(0, GetRotation().y, 0),
		Vector3(0, 0, GetRotation().z)
	};

	Vector3 t_Test2[3] = {
		Vector3(other.GetRotation().x, 0, 0),
		Vector3(0, other.GetRotation().y, 0),
		Vector3(0, 0, other.GetRotation().z)
	};

	// Compute rotation matrix expressing b in a's coordinate frame
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			t_R.m[i][j] = Vector::CalculateDotProduct(t_Test1[i], t_Test2[j]);
		}
	}
	
	// Compute Translation Vector3 t
	Vector3 t_Translation = other.GetPosition() - GetPosition();
	float t_TranslationArray[3];

	// Bring Translation into a's coordinate frame
	t_Translation = Vector3(Vector::CalculateDotProduct(t_Translation, t_Test1[0]), Vector::CalculateDotProduct(t_Translation, t_Test1[1]), Vector::CalculateDotProduct(t_Translation, t_Test1[2]));

	// Compute common sub-expressions. Add in an epsion term to conteract arithemtic errors when two edges are parallel and their cross product is (near) null (see text for details)
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			t_AbsR.m[i][j] = std::abs(t_R.m[i][j]) + FLT_EPSILON;
		}
	}

	// Translate Vector 3 into Float Array
	t_TranslationArray[0] = t_Translation.x;
	t_TranslationArray[1] = t_Translation.y;
	t_TranslationArray[2] = t_Translation.z;

	// Test Axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; ++i)
	{
		t_RA = m_Extents[i];
		t_RB = other.m_Extents[0] * t_AbsR.m[i][0] + other.m_Extents[1] * t_AbsR.m[i][1] + other.m_Extents[2] * t_AbsR.m[i][2];
		if (std::abs(t_TranslationArray[i]) > t_RA + t_RB) { return false; }
	}

	// Test Axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; ++i)
	{
		t_RA = m_Extents[0] * t_AbsR.m[0][i] + m_Extents[1] * t_AbsR.m[1][i] + m_Extents[2] * t_AbsR.m[2][i];
		t_RB = other.m_Extents[i];
		if (std::abs(t_TranslationArray[i] * t_R.m[0][i] + t_TranslationArray[1] * t_R.m[1][i] + t_TranslationArray[2] * t_R.m[2][i]) > t_RA + t_RB) { return false; }
	}

	// Test Axis L = A0 x B0
	t_RA =       m_Extents[1] * t_AbsR.m[2][0] +       m_Extents[2] * t_AbsR.m[1][0];
	t_RB = other.m_Extents[1] * t_AbsR.m[0][2] + other.m_Extents[2] * t_AbsR.m[0][1];
	if (std::abs(t_TranslationArray[2] * t_R.m[1][0] - t_TranslationArray[1] * t_R.m[2][0]) > t_RA + t_RB) { return false; }

	// Test Axis L = A0 x B1
	t_RA =       m_Extents[1] * t_AbsR.m[2][1] +       m_Extents[2] * t_AbsR.m[1][1];
	t_RB = other.m_Extents[0] * t_AbsR.m[0][2] + other.m_Extents[2] * t_AbsR.m[0][0];
	if (std::abs(t_TranslationArray[2] * t_R.m[1][1] - t_TranslationArray[1] * t_R.m[2][1]) > t_RA + t_RB) { return false; }

	// Test Axis L = A0 x B2
	t_RA =       m_Extents[1] * t_AbsR.m[2][2] +       m_Extents[2] * t_AbsR.m[1][2];
	t_RB = other.m_Extents[0] * t_AbsR.m[0][1] + other.m_Extents[1] * t_AbsR.m[0][0];
	if (std::abs(t_TranslationArray[2] * t_R.m[1][2] - t_TranslationArray[1] * t_R.m[2][2]) > t_RA + t_RB) { return false; }



	// Test Axis L = A1 x B0
	t_RA =       m_Extents[0] * t_AbsR.m[2][0] +       m_Extents[2] * t_AbsR.m[0][0];
	t_RB = other.m_Extents[1] * t_AbsR.m[1][2] + other.m_Extents[2] * t_AbsR.m[1][1];
	if (std::abs(t_TranslationArray[0] * t_R.m[2][0] - t_TranslationArray[2] * t_R.m[0][0]) > t_RA + t_RB) { return false; }

	// Test Axis L = A1 x B1
	t_RA =       m_Extents[0] * t_AbsR.m[2][1] +       m_Extents[2] * t_AbsR.m[0][1];
	t_RB = other.m_Extents[0] * t_AbsR.m[1][2] + other.m_Extents[2] * t_AbsR.m[1][0];
	if (std::abs(t_TranslationArray[0] * t_R.m[2][1] - t_TranslationArray[2] * t_R.m[0][1]) > t_RA + t_RB) { return false; }

	// Test Axis L = A1 x B2
	t_RA =       m_Extents[0] * t_AbsR.m[2][2] +       m_Extents[2] * t_AbsR.m[0][2];
	t_RB = other.m_Extents[0] * t_AbsR.m[1][1] + other.m_Extents[1] * t_AbsR.m[1][0];
	if (std::abs(t_TranslationArray[0] * t_R.m[2][2] - t_TranslationArray[2] * t_R.m[0][2]) > t_RA + t_RB) { return false; }



	// Test Axis L = A2 x B0
	t_RA =       m_Extents[0] * t_AbsR.m[1][0] +       m_Extents[1] * t_AbsR.m[0][0];
	t_RB = other.m_Extents[1] * t_AbsR.m[2][2] + other.m_Extents[2] * t_AbsR.m[2][1];
	if (std::abs(t_TranslationArray[1] * t_R.m[0][0] - t_TranslationArray[0] * t_R.m[1][0]) > t_RA + t_RB) { return false; }

	// Test Axis L = A2 x B1
	t_RA =       m_Extents[0] * t_AbsR.m[1][1] +       m_Extents[1] * t_AbsR.m[0][1];
	t_RB = other.m_Extents[0] * t_AbsR.m[2][2] + other.m_Extents[2] * t_AbsR.m[2][0];
	if (std::abs(t_TranslationArray[1] * t_R.m[0][1] - t_TranslationArray[0] * t_R.m[1][1]) > t_RA + t_RB) { return false; }

	// Test Axis L = A2 x B2
	t_RA =       m_Extents[0] * t_AbsR.m[1][2] +       m_Extents[1] * t_AbsR.m[0][2];
	t_RB = other.m_Extents[0] * t_AbsR.m[2][1] + other.m_Extents[1] * t_AbsR.m[2][0];
	if (std::abs(t_TranslationArray[1] * t_R.m[0][2] - t_TranslationArray[0] * t_R.m[1][2]) > t_RA + t_RB) { return false; }

	// Not Seperating Axis, There is a Collision

	out.collisionNormal = other.GetPosition() - GetPosition();
	out.contactPointCount = 1;
	out.penetrationDepth = 0.0001f;

	return true;
}

bool OBBCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{



	return false;
}

bool OBBCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{



	return false;
}

bool OBBCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{



	return false;
}

bool OBBCollider::CollidesWith(SATCollider& other, CollisionManifold& out)
{
	return false;
}

Vector3 OBBCollider::NearestPoint(Vector3 point)
{
	// TODO: Revise this Function
	Vector3 t_Result = GetPosition();
	Vector3 t_Direction = point - GetPosition();

	for (int i = 0; i < 3; ++i)
	{
		Vector3 t_Axis = m_Orientation; // Testing one Axis at a Time || NOTE: Fills all 3 axis with the same value for the check value, Implement this
		float t_Distance = Vector::CalculateDotProduct(t_Direction, t_Axis);

		if (t_Distance > m_Size[i]) { t_Distance = m_Size[i]; }
		if (t_Distance < -m_Size[i]) { t_Distance = -m_Size[i]; }
		t_Result = t_Result + (t_Axis * t_Distance);
	}

	return t_Result;
}

bool OBBCollider::PointInOBB(Vector3 point)
{
	Vector3 t_Direction = point - GetPosition();

	for (int i = 0; i < 3; ++i)
	{
		Vector3 t_Axis = m_Orientation;
		float t_Distance = Vector::CalculateDotProduct(t_Direction, t_Axis);

		if (t_Distance > m_Size[i])
		{
			return false;
		}

		if (t_Distance < -m_Size[i])
		{
			return false;
		}
	}

	return true;
}
