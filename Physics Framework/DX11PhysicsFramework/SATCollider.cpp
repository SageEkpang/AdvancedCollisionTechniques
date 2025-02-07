#include "SATCollider.h"
#include "BoxCollider.h"


SATCollider::SATCollider(Transform* transform, Interval interval)
{
	// m_SATInterval = interval;
}

SATCollider::~SATCollider()
{

}

bool SATCollider::ObjectCollision(OBBCollider* objectA, OBBCollider* objectB, CollisionManifold& out)
{
	float t_RA, t_RB;
	XMFLOAT3X3 t_R, t_AbsR;

	float m_ExtentsA[3];
	float m_ExtentsB[3];

	m_ExtentsA[0] = objectA->GetTransform()->GetScale().x / 4;
	m_ExtentsA[1] = objectA->GetTransform()->GetScale().y / 4;
	m_ExtentsA[2] = objectA->GetTransform()->GetScale().z / 4;

	m_ExtentsB[0] = objectB->GetTransform()->GetScale().x / 4;
	m_ExtentsB[1] = objectB->GetTransform()->GetScale().y / 4;
	m_ExtentsB[2] = objectB->GetTransform()->GetScale().z / 4;

	Vector3 t_Test1[3] = {

		Vector3(1, 0, 0),
		Vector3(0, 1, 0),
		Vector3(0, 0, 1)
	};

	Vector3 t_Test2[3] = {
		Vector3(1, 0, 0),
		Vector3(0, 1, 0),
		Vector3(0, 0, 1)
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
	Vector3 t_Translation = objectB->GetTransform()->GetPosition() - objectA->GetTransform()->GetPosition();

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
	float t_TranslationArray[3];
	t_TranslationArray[0] = t_Translation.x;
	t_TranslationArray[1] = t_Translation.y;
	t_TranslationArray[2] = t_Translation.z;

	// Test Axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; ++i)
	{
		t_RA = m_ExtentsA[i];
		t_RB = m_ExtentsB[0] * t_AbsR.m[i][0] + m_ExtentsB[1] * t_AbsR.m[i][1] + m_ExtentsB[2] * t_AbsR.m[i][2];
		if (std::abs(t_TranslationArray[i]) > t_RA + t_RB) { return false; }
	}

	// Test Axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; ++i)
	{
		t_RA = m_ExtentsA[0] * t_AbsR.m[0][i] + m_ExtentsA[1] * t_AbsR.m[1][i] + m_ExtentsA[2] * t_AbsR.m[2][i];
		t_RB = m_ExtentsB[i];
		if (std::abs(t_TranslationArray[i] * t_R.m[0][i] + t_TranslationArray[1] * t_R.m[1][i] + t_TranslationArray[2] * t_R.m[2][i]) > t_RA + t_RB) { return false; }
	}

	// Test Axis L = A0 x B0
	t_RA = m_ExtentsA[1] * t_AbsR.m[2][0] + m_ExtentsA[2] * t_AbsR.m[1][0];
	t_RB = m_ExtentsB[1] * t_AbsR.m[0][2] + m_ExtentsB[2] * t_AbsR.m[0][1];
	if (std::abs(t_TranslationArray[2] * t_R.m[1][0] - t_TranslationArray[1] * t_R.m[2][0]) > t_RA + t_RB) { return false; }

	// Test Axis L = A0 x B1
	t_RA = m_ExtentsA[1] * t_AbsR.m[2][1] + m_ExtentsA[2] * t_AbsR.m[1][1];
	t_RB = m_ExtentsB[0] * t_AbsR.m[0][2] + m_ExtentsB[2] * t_AbsR.m[0][0];
	if (std::abs(t_TranslationArray[2] * t_R.m[1][1] - t_TranslationArray[1] * t_R.m[2][1]) > t_RA + t_RB) { return false; }

	// Test Axis L = A0 x B2
	t_RA = m_ExtentsA[1] * t_AbsR.m[2][2] + m_ExtentsA[2] * t_AbsR.m[1][2];
	t_RB = m_ExtentsB[0] * t_AbsR.m[0][1] + m_ExtentsB[1] * t_AbsR.m[0][0];
	if (std::abs(t_TranslationArray[2] * t_R.m[1][2] - t_TranslationArray[1] * t_R.m[2][2]) > t_RA + t_RB) { return false; }



	// Test Axis L = A1 x B0
	t_RA = m_ExtentsA[0] * t_AbsR.m[2][0] + m_ExtentsA[2] * t_AbsR.m[0][0];
	t_RB = m_ExtentsB[1] * t_AbsR.m[1][2] + m_ExtentsB[2] * t_AbsR.m[1][1];
	if (std::abs(t_TranslationArray[0] * t_R.m[2][0] - t_TranslationArray[2] * t_R.m[0][0]) > t_RA + t_RB) { return false; }

	// Test Axis L = A1 x B1
	t_RA = m_ExtentsA[0] * t_AbsR.m[2][1] + m_ExtentsA[2] * t_AbsR.m[0][1];
	t_RB = m_ExtentsB[0] * t_AbsR.m[1][2] + m_ExtentsB[2] * t_AbsR.m[1][0];
	if (std::abs(t_TranslationArray[0] * t_R.m[2][1] - t_TranslationArray[2] * t_R.m[0][1]) > t_RA + t_RB) { return false; }

	// Test Axis L = A1 x B2
	t_RA = m_ExtentsA[0] * t_AbsR.m[2][2] + m_ExtentsA[2] * t_AbsR.m[0][2];
	t_RB = m_ExtentsB[0] * t_AbsR.m[1][1] + m_ExtentsB[1] * t_AbsR.m[1][0];
	if (std::abs(t_TranslationArray[0] * t_R.m[2][2] - t_TranslationArray[2] * t_R.m[0][2]) > t_RA + t_RB) { return false; }



	// Test Axis L = A2 x B0
	t_RA = m_ExtentsA[0] * t_AbsR.m[1][0] + m_ExtentsA[1] * t_AbsR.m[0][0];
	t_RB = m_ExtentsB[1] * t_AbsR.m[2][2] + m_ExtentsB[2] * t_AbsR.m[2][1];
	if (std::abs(t_TranslationArray[1] * t_R.m[0][0] - t_TranslationArray[0] * t_R.m[1][0]) > t_RA + t_RB) { return false; }

	// Test Axis L = A2 x B1
	t_RA = m_ExtentsA[0] * t_AbsR.m[1][1] + m_ExtentsA[1] * t_AbsR.m[0][1];
	t_RB = m_ExtentsB[0] * t_AbsR.m[2][2] + m_ExtentsB[2] * t_AbsR.m[2][0];
	if (std::abs(t_TranslationArray[1] * t_R.m[0][1] - t_TranslationArray[0] * t_R.m[1][1]) > t_RA + t_RB) { return false; }

	// Test Axis L = A2 x B2
	t_RA = m_ExtentsA[0] * t_AbsR.m[1][2] + m_ExtentsA[1] * t_AbsR.m[0][2];
	t_RB = m_ExtentsB[0] * t_AbsR.m[2][1] + m_ExtentsB[1] * t_AbsR.m[2][0];
	if (std::abs(t_TranslationArray[1] * t_R.m[0][2] - t_TranslationArray[0] * t_R.m[1][2]) > t_RA + t_RB) { return false; }

	// Not Seperating Axis, There is a Collision

	out.collisionNormal = objectB->GetTransform()->GetPosition() - objectA->GetTransform()->GetPosition();
	out.contactPointCount = 1.0;
	out.penetrationDepth = 0.0001f;

	return true;
}

bool SATCollider::OverlapAxis(BoxCollider* box, Vector3* axis)
{
	Interval t_ShapeA = Vector::GetInterval(box, axis);
	Interval t_ShapeB = Vector::GetInterval(box, axis);

	return (t_ShapeB.min <= t_ShapeA.max) && (t_ShapeA.min <= t_ShapeB.max);
}
