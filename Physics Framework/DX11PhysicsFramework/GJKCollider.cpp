//#include "GJKCollider.h"
//
//GJKCollider::GJKCollider()
//{
//	printf("GJK Collider Set Up");
//}
//
//GJKCollider::~GJKCollider()
//{
//
//}
//
//CollisionManifold GJKCollider::GJKCollision(Collider* colliderA, Collider* colliderB)
//{
//	Vector3 t_Support = Support(colliderA, colliderB, Vector3(1, 0, 0));
//
//	// Simplex is an array of points, max count is 4
//	Simplex t_Points;
//	t_Points.push_front(t_Support);
//
//	Vector3 t_Direction = t_Support * -1;
//
//	for (int i = 0; i < 100; ++i)
//	{
//		// NOTE: Check the Collider A and ColliderB Context
//		t_Support = Support(colliderA, colliderB, t_Direction);
//	
//		float t_Dis = Vector::CalculateDotProductNotNorm(t_Support, t_Direction); // FIXME: Might need to use the NotNorm version of this
//
//		// NOTE: No Collision
//		if ( t_Dis <= 0) { return false; }
//
//		// NOTE: Check the Simplex that the Collision Lies in
//		t_Points.push_front(t_Support);
//
//		if (NextSimplex(t_Points, t_Direction)) 
//		{ 
//			CollisionManifold t_CollisionManifold = CollisionManifold();
//
//			m_OutSimplex = t_Points;
//			t_Points = Simplex();
//
//			t_CollisionManifold.collisionNormal = colliderA->GetPosition() - colliderB->GetPosition();
//			t_CollisionManifold.penetrationDepth = 1.0f;
//			t_CollisionManifold.hasCollision = true;
//
//			return t_CollisionManifold; 
//		}
//	}
//}
//
//CollisionManifold GJKCollider::S_GJKCollision(GameObject* objectA, GameObject* objectB)
//{
//	Collider* t_ColliderA = objectA->GetCollider();
//	Collider* t_ColliderB = objectB->GetCollider();
//
//	Vector3 t_Support = Support(t_ColliderA, t_ColliderB, Vector3(1, 0, 0));
//
//	// Simplex is an array of points, max count is 4
//	Simplex t_Points;
//	t_Points.push_front(t_Support);
//
//	Vector3 t_Direction = t_Support * -1;
//
//	for (int i = 0; i < 100; ++i)
//	{
//		// NOTE: Check the Collider A and ColliderB Context
//		t_Support = Support(t_ColliderA, t_ColliderB, t_Direction);
//
//		float t_Dis = Vector::CalculateDotProductNotNorm(t_Support, t_Direction); // FIXME: Might need to use the NotNorm version of this
//
//		// NOTE: No Collision
//		if (t_Dis <= 0) { return false; }
//
//		// NOTE: Check the Simplex that the Collision Lies in
//		t_Points.push_front(t_Support);
//
//		if (NextSimplex(t_Points, t_Direction))
//		{
//			CollisionManifold t_CollisionManifold = CollisionManifold();
//
//			t_Points = Simplex();
//
//			t_CollisionManifold.collisionNormal = t_ColliderA->GetPosition() - t_ColliderB->GetPosition();
//			t_CollisionManifold.penetrationDepth = 1.0f;
//			t_CollisionManifold.hasCollision = true;
//
//			return t_CollisionManifold;
//		}
//	}
//
//
//
//	return CollisionManifold();
//}
//
//bool GJKCollider::NextSimplex(Simplex& points, Vector3& direction)
//{
//	switch (points.GetSize())
//	{
//		case 2: return Line(points, direction);
//		case 3: return Triangle(points, direction);
//		case 4: return Tetrahedron(points, direction);
//	}
//
//	// NOTE: Should not Get Here
//	return false;
//}
//
//bool GJKCollider::Line(Simplex& points, Vector3& direction)
//{
//	// NOTE: Check if the Point Ever Intersects the Line at All
//	Vector3 t_A = points[0];
//	Vector3 t_B = points[1];
//
//	Vector3 t_AB = t_B - t_A;
//	Vector3 t_AO = -t_A;
//
//	if (SameDirection(t_AB, t_AO))
//	{
//		direction = Vector::CalculateCrossProductV(Vector::CalculateCrossProductV(t_AB, t_AO), t_AB);
//	}
//	else
//	{
//		points = { t_A };
//		direction = t_AO;
//	}
//
//	return false;
//}
//
//bool GJKCollider::Triangle(Simplex& points, Vector3& direction)
//{
//	// NOTE: Checks if the point intersects the Triangle at all
//	Vector3 t_A = points[0];
//	Vector3 t_B = points[1];
//	Vector3 t_C = points[2];
//
//	Vector3 t_AB = t_B - t_A;
//	Vector3 t_AC = t_C - t_A;
//	Vector3 t_AO = -t_A;
//
//	Vector3 t_ABC = Vector::CalculateCrossProductV(t_AB, t_AC);
//
//	if (SameDirection(Vector::CalculateCrossProductV(t_ABC, t_AC), t_AO))
//	{
//		if (SameDirection(t_AC, t_AO))
//		{
//			points = { t_A, t_C }; // Fix this
//			direction = Vector::CalculateCrossProductV(Vector::CalculateCrossProductV(t_AC, t_AO), t_AC);
//		}
//		else
//		{
//			return Line(points = { t_A, t_B }, direction);
//		}
//	}
//	else
//	{
//		if (SameDirection(Vector::CalculateCrossProductV(t_AB, t_ABC), t_AO))
//		{
//			return Line(points = { t_A, t_B}, direction);
//		}
//		else
//		{
//			if (SameDirection(t_ABC, t_AO))
//			{
//				direction = t_ABC;
//			}
//			else
//			{
//				points = { t_A, t_C, t_B };
//				direction = -t_ABC;
//			}
//		}
//	}
//
//	return false;
//}
//
//bool GJKCollider::Tetrahedron(Simplex& points, Vector3& direction)
//{
//	// NOTE: Check if the point is inside the Tetrahedron and if there even is a point inside
//	Vector3 t_A = points[0];
//	Vector3 t_B = points[1];
//	Vector3 t_C = points[2];
//	Vector3 t_D = points[3];
//
//	Vector3 t_AB = t_B - t_A;
//	Vector3 t_AC = t_C - t_A;
//	Vector3 t_AD = t_D - t_A;
//	Vector3 t_AO = -t_A;
//
//	Vector3 t_ABC = Vector::CalculateCrossProductV(t_AB, t_AC);
//	Vector3 t_ACD = Vector::CalculateCrossProductV(t_AC, t_AD);
//	Vector3 t_ADB = Vector::CalculateCrossProductV(t_AD, t_AB);
//
//	if (SameDirection(t_ABC, t_AO))
//	{
//		return Triangle(points = {t_A, t_B, t_C}, direction);
//	}
//
//	if (SameDirection(t_ACD, t_AO))
//	{
//		return Triangle(points = {t_A, t_C, t_D}, direction);
//	}
//
//	if (SameDirection(t_ADB, t_AO))
//	{
//		return Triangle(points = {t_A, t_D, t_B}, direction);
//	}
//
//	return true;
//}
//
//bool GJKCollider::SameDirection(Vector3 direction, Vector3 Ao)
//{
//	// NOTE: Calculate the direction of the vectors pointing in the direction of the AO
//	return Vector::CalculateDotProduct(direction, Ao) > 0;
//}
//
//Vector3 GJKCollider::Support(Collider* colliderA, Collider* colliderB, Vector3 direction)
//{
//	Vector3 t_TempA = colliderA->FindFurthestPoint(direction);
//	Vector3 t_TempB = colliderB->FindFurthestPoint(-direction);
//
//	return t_TempA - t_TempB;
//}
//
