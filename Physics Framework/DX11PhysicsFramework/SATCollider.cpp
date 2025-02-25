#include "SATCollider.h"
#include "BoxCollider.h"


SATCollider::SATCollider()
{
	printf("SAT Collider Set Up"); // NOTE: Due to debug stream, this will not work
}

SATCollider::~SATCollider()
{
	
}

CollisionManifold SATCollider::SATCollision(GameObject& objectA, GameObject& objectB)
{
	CollisionManifold t_CollisionManifold;

	// NOTE: Fill Orientation Array (A)
	float t_OrA[9];
	{
		t_OrA[0] = objectA.GetTransform()->GetRotation().x;
		t_OrA[1] = 0;
		t_OrA[2] = 0;

		t_OrA[3] = 0;
		t_OrA[4] = objectA.GetTransform()->GetRotation().y;
		t_OrA[5] = 0;

		t_OrA[6] = 0;
		t_OrA[7] = 0;
		t_OrA[8] = objectA.GetTransform()->GetRotation().z;
	}

	// NOTE: Fill Orientation Array (B)
	float t_OrB[9];
	{
		t_OrB[0] = objectB.GetTransform()->GetRotation().x;
		t_OrB[1] = 0;
		t_OrB[2] = 0;

		t_OrB[3] = 0;
		t_OrB[4] = objectB.GetTransform()->GetRotation().y;
		t_OrB[5] = 0;

		t_OrB[6] = 0;
		t_OrB[7] = 0;
		t_OrB[8] = objectB.GetTransform()->GetRotation().z;
	}

	// NOTE: Set up tests
	Vector3 t_Test[15] = {
		Vector3(t_OrA[0], t_OrA[1], t_OrA[2]),
		Vector3(t_OrA[3], t_OrA[4], t_OrA[5]),
		Vector3(t_OrA[6], t_OrA[7], t_OrA[8]),

		Vector3(t_OrB[0], t_OrB[1], t_OrB[2]),
		Vector3(t_OrB[3], t_OrB[4], t_OrB[5]),
		Vector3(t_OrB[6], t_OrB[7], t_OrB[8])
	};

	// NOTE: Insert Differnet Axis into Array
	for (int i = 0; i < 3; ++i)
	{
		t_Test[6 + i * 3 + 0] = Vector::CalculateCrossProductV(t_Test[i], t_Test[0]);
		t_Test[6 + i * 3 + 1] = Vector::CalculateCrossProductV(t_Test[i], t_Test[1]);
		t_Test[6 + i * 3 + 2] = Vector::CalculateCrossProductV(t_Test[i], t_Test[2]);
	}

	// NOTE: Do the Seperating Axis Tests
	for (int i = 0; i < 15; ++i)
	{
		bool t_Overlapping = OverlapOnAxis(objectA, objectB, t_Test[i]);
		if (!t_Overlapping)
		{
			return false; // Seperating Axis was found (There is not a collision)
		}
	}

	t_CollisionManifold.hasCollision = true;
	t_CollisionManifold.collisionNormal = objectA.GetTransform()->GetPosition() - objectB.GetTransform()->GetPosition();
	t_CollisionManifold.penetrationDepth = 1.0;

	return t_CollisionManifold;  // Seperating Axis not Found (There was Collision)
}

CollisionManifold SATCollider::S_SATCollision(GameObject* objectA, GameObject* objectB)
{
	CollisionManifold t_CollisionManifold;

	// NOTE: Fill Orientation Array (A)
	float t_OrA[9];
	{
		t_OrA[0] = objectA->GetTransform()->GetRotation().x;
		t_OrA[1] = 0;
		t_OrA[2] = 0;

		t_OrA[3] = 0;
		t_OrA[4] = objectA->GetTransform()->GetRotation().y;
		t_OrA[5] = 0;

		t_OrA[6] = 0;
		t_OrA[7] = 0;
		t_OrA[8] = objectA->GetTransform()->GetRotation().z;
	}

	// NOTE: Fill Orientation Array (B)
	float t_OrB[9];
	{
		t_OrB[0] = objectB->GetTransform()->GetRotation().x;
		t_OrB[1] = 0;
		t_OrB[2] = 0;

		t_OrB[3] = 0;
		t_OrB[4] = objectB->GetTransform()->GetRotation().y;
		t_OrB[5] = 0;

		t_OrB[6] = 0;
		t_OrB[7] = 0;
		t_OrB[8] = objectB->GetTransform()->GetRotation().z;
	}

	// NOTE: Set up tests
	Vector3 t_Test[15] = {
		Vector3(t_OrA[0], t_OrA[1], t_OrA[2]),
		Vector3(t_OrA[3], t_OrA[4], t_OrA[5]),
		Vector3(t_OrA[6], t_OrA[7], t_OrA[8]),

		Vector3(t_OrB[0], t_OrB[1], t_OrB[2]),
		Vector3(t_OrB[3], t_OrB[4], t_OrB[5]),
		Vector3(t_OrB[6], t_OrB[7], t_OrB[8])
	};

	// NOTE: Insert Differnet Axis into Array
	for (int i = 0; i < 3; ++i)
	{
		t_Test[6 + i * 3 + 0] = Vector::CalculateCrossProductV(t_Test[i], t_Test[0]);
		t_Test[6 + i * 3 + 1] = Vector::CalculateCrossProductV(t_Test[i], t_Test[1]);
		t_Test[6 + i * 3 + 2] = Vector::CalculateCrossProductV(t_Test[i], t_Test[2]);
	}

	// NOTE: Do the Seperating Axis Tests
	for (int i = 0; i < 15; ++i)
	{
		bool t_Overlapping = OverlapOnAxis(*objectA, *objectB, t_Test[i]);
		if (!t_Overlapping)
		{
			return false; // Seperating Axis was found (There is not a collision)
		}
	}

	t_CollisionManifold.hasCollision = true;
	t_CollisionManifold.collisionNormal = objectA->GetTransform()->GetPosition() - objectB->GetTransform()->GetPosition();
	t_CollisionManifold.penetrationDepth = 1.0;

	return t_CollisionManifold;  // Seperating Axis not Found (There was Collision)
}

bool SATCollider::OverlapOnAxis(GameObject& satA, GameObject& satB, Vector3& axis)
{
	Interval t_A = GetIntervalOr(satA, axis);
	Interval t_B = GetIntervalOr(satB, axis);
	bool t_ExtentCheck = (t_B.min <= t_A.max) && (t_A.min <= t_B.max);

	return t_ExtentCheck;
}

Interval SATCollider::GetIntervalOr(GameObject& object, Vector3& axis)
{
	Vector3 t_Vertex[8];
	Vector3 t_Position = object.GetTransform()->GetPosition();
	Vector3 t_Size = object.GetTransform()->GetScale();

	// NOTE: Init Rotation Function
	float t_Orientation[9];
	{
		t_Orientation[0] = object.GetTransform()->GetRotation().x;
		t_Orientation[1] = 0;
		t_Orientation[2] = 0;

		t_Orientation[3] = 0;
		t_Orientation[4] = object.GetTransform()->GetRotation().y;
		t_Orientation[5] = 0;

		t_Orientation[6] = 0;
		t_Orientation[7] = 0;
		t_Orientation[8] = object.GetTransform()->GetRotation().z;
	}

	Vector3 t_Axis[] = {
		Vector3(t_Orientation[0], t_Orientation[1], t_Orientation[2]),
		Vector3(t_Orientation[3], t_Orientation[4], t_Orientation[5]),
		Vector3(t_Orientation[6], t_Orientation[7], t_Orientation[8])
	};

	t_Vertex[0] = (t_Position + t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);
	t_Vertex[1] = (t_Position - t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);
	t_Vertex[2] = (t_Position + t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);
	t_Vertex[3] = (t_Position + t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[4] = (t_Position - t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[5] = (t_Position + t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[6] = (t_Position - t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[7] = (t_Position - t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);

	Interval t_Result;
	t_Result.max = Vector::CalculateDotProductNotNorm(axis, t_Vertex[0]);
	t_Result.min = Vector::CalculateDotProductNotNorm(axis, t_Vertex[0]);

	for (int i = 1; i < 8; ++i)
	{
		float t_Projection = Vector::CalculateDotProductNotNorm(axis, t_Vertex[i]);
		t_Result.min = (t_Projection < t_Result.min) ? t_Projection : t_Result.min;
		t_Result.max = (t_Projection > t_Result.max) ? t_Projection : t_Result.max;
	}

	return t_Result;
}
