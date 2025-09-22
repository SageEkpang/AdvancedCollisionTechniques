#include "CollisionManager.h"

// GJK
// Minkowaski Difference Function
Vector3 CollisionManager::FindFurthestPoint(GameObjectEntity* gjkA, Vector3 direction)
{
	// STEP 1: Find the Max Point
	Vector3 t_MaxPoint;
	float t_MaxDistance = -FLT_MAX;

	// NOTE: Find furthest vertex
	for (Vector3& v : gjkA->GetComponent<GJKCollider>()->m_PositionStore)
	{
		float t_Distance = v.Dot(direction);

		if (t_Distance > t_MaxDistance)
		{
			t_MaxDistance = t_Distance;
			t_MaxPoint = v;
		}
	}
	
	return t_MaxPoint;
}

bool CollisionManager::Line(Simplex& points, Vector3& direction)
{
	// NOTE: Check if the Point Ever Intersects the Line at All
	Vector3 t_A = points[0];
	Vector3 t_B = points[1];

	Vector3 t_AB = t_B - t_A;
	Vector3 t_AO =     - t_A;

	if (SameDirection(t_AB, t_AO))
	{
		
		direction = Vector3::S_Cross(Vector3::S_Cross(t_AB, t_AO), t_AB);
	}
	else
	{
		points = { t_A };
		direction = t_AO;
	}

	return false;
}

bool CollisionManager::Triangle(Simplex& points, Vector3& direction)
{
	// NOTE: Checks if the point intersects the Triangle at all
	Vector3 t_A = points[0];
	Vector3 t_B = points[1];
	Vector3 t_C = points[2];

	Vector3 t_AB = t_B - t_A;
	Vector3 t_AC = t_C - t_A;
	Vector3 t_AO = - t_A;

	Vector3 t_ABC = Vector3::S_Cross(t_AB, t_AC);

	if (SameDirection(Vector3::S_Cross(t_ABC, t_AC), t_AO))
	{
		if (SameDirection(t_AC, t_AO))
		{
			points = { t_A, t_C }; // Fix this
			direction = Vector3::S_Cross(Vector3::S_Cross(t_AC, t_AO), t_AC);
		}
		else
		{
			return Line(points = { t_A, t_B }, direction);
		}
	}
	else
	{
		if (SameDirection(Vector3::S_Cross(t_AB, t_ABC), t_AO))
		{
			return Line(points = { t_A, t_B}, direction);
		}
		else
		{
			if (SameDirection(t_ABC, t_AO))
			{
				direction = t_ABC;
			}
			else
			{
				points = { t_A, t_C, t_B };
				direction = -t_ABC;
			}
		}
	}

	return false;
}

bool CollisionManager::Tetrahedron(Simplex& points, Vector3& direction)
{
	// NOTE: Check if the point is inside the Tetrahedron and if there even is a point inside
	Vector3 t_A = points[0];
	Vector3 t_B = points[1];
	Vector3 t_C = points[2];
	Vector3 t_D = points[3];
	
	Vector3 t_AB = t_B - t_A;
	Vector3 t_AC = t_C - t_A;
	Vector3 t_AD = t_D - t_A;
	Vector3 t_AO = - t_A;
	
	Vector3 t_ABC = Vector3::S_Cross(t_AB, t_AC);
	Vector3 t_ACD = Vector3::S_Cross(t_AC, t_AD);
	Vector3 t_ADB = Vector3::S_Cross(t_AD, t_AB);
	
	if (SameDirection(t_ABC, t_AO))
	{
		return Triangle(points = {t_A, t_B, t_C}, direction);
	}
	
	if (SameDirection(t_ACD, t_AO))
	{
		return Triangle(points = {t_A, t_C, t_D}, direction);
	}
	
	if (SameDirection(t_ADB, t_AO))
	{
		return Triangle(points = {t_A, t_D, t_B}, direction);
	}
	
	return true;
}

bool CollisionManager::SameDirection(const Vector3& direction, const Vector3& ao)
{
	return direction.Dot(ao) > 0;
}

Vector3 CollisionManager::Support(GameObjectEntity* colliderA, GameObjectEntity* colliderB, Vector3 direction)
{
	Vector3 t_TempA = FindFurthestPoint(colliderA, direction);

	Vector3 testing = -direction;
	Vector3 t_TempB = FindFurthestPoint(colliderB, -direction);
	return t_TempA - t_TempB;
}

bool CollisionManager::NextSimplex(Simplex& points, Vector3& direction)
{
	switch (points.size())
	{
		case 2: return Line		  (points, direction);
		case 3: return Triangle   (points, direction);
		case 4: return Tetrahedron(points, direction);
	}
	
	// NOTE: Should not get Here
	return false;
}

CollisionManager::CollisionManager()
{
	m_CollisionMapping[std::make_pair(std::type_index(typeid(SphereCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_SPHERE_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(BoxCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_BOX_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(BoxCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_BOX_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(PlaneCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_PLANE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(SATCollider)), std::type_index(typeid(SATCollider)))] = COLLIDER_TYPE_COLLISIONS_SAT_TO_SAT;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(SATCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_SAT_TO_BOX;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(EPACollider)), std::type_index(typeid(EPACollider)))] = COLLIDER_TYPE_COLLISIONS_EPA_TO_EPA;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(GJKCollider)), std::type_index(typeid(GJKCollider)))] = COLLIDER_TYPE_COLLISIONS_GJK_TO_GJK;
}

CollisionManager::~CollisionManager()
{
	m_CollisionMapping.clear();
}

CollisionManifold CollisionManager::CheckCollisions(GameObjectEntity* colliderA, GameObjectEntity* colliderB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// NOTE: Temp Collision Variables
	GameObjectEntity* tempA = nullptr;
	GameObjectEntity* tempB = nullptr;

	// NOTE: Check if the collider component exists within the game object
	if (colliderA->FindChildComponent<ColliderEntity>()) { tempA = colliderA; }
	if (colliderB->FindChildComponent<ColliderEntity>()) { tempB = colliderB; }
	if (tempA == nullptr || tempB == nullptr) { return CollisionManifold(); }

	// NOTE: Assign the static casted class to the Game Objects
	auto collision_made_pair = std::make_pair(tempA->FindChildComponentID<ColliderEntity>(), tempB->FindChildComponentID<ColliderEntity>());

	// NOTE: Reverse pair if it is not within the collision map
	if (m_CollisionMapping.count(collision_made_pair) == 0)
	{
		std::swap(collision_made_pair.first, collision_made_pair.second);
		std::swap(tempA, tempB);
	}

	switch (m_CollisionMapping[collision_made_pair])
	{
		case COLLIDER_TYPE_COLLISIONS_SPHERE_TO_SPHERE: return t_ColMani = SphereToSphere(tempA, tempB); break;
		
		case COLLIDER_TYPE_COLLISIONS_BOX_TO_BOX: return t_ColMani = BoxToBox(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_BOX_TO_SPHERE: return t_ColMani = BoxToSphere(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_PLANE_TO_PLANE: return t_ColMani = PlaneToPlane(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_PLANE_TO_BOX: return t_ColMani = PlaneToBox(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_PLANE_TO_SPHERE: return t_ColMani = PlaneToSphere(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_SAT_TO_SAT: return t_ColMani = SATtoSAT(tempA, tempB); break;
		case COLLIDER_TYPE_COLLISIONS_SAT_TO_BOX: return t_ColMani = SATtoBox(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_EPA_TO_EPA: return t_ColMani = EPAtoEPA(tempA, tempB); break;

		case COLLIDER_TYPE_COLLISIONS_GJK_TO_GJK: return t_ColMani = GJKtoGJK(tempA, tempB); break;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::SphereToSphere(GameObjectEntity* sphereA, GameObjectEntity* sphereB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 SphereAPosition = sphereA->m_Transform.m_Position;
	const float SphereARadius = sphereA->GetComponent<SphereCollider>()->m_Radius;

	Vector3 SphereBPosition = sphereB->m_Transform.m_Position;
	const float SphereBRadius = sphereB->GetComponent<SphereCollider>()->m_Radius;

	float t_Distance = Vector3(SphereAPosition - SphereBPosition).Magnitude();
	float t_RadiiSum = SphereARadius + SphereBRadius;

	if (t_Distance <= t_RadiiSum)
	{
		t_ColMani.hasCollision = true;
		t_ColMani.collisionNormal = Vector3(SphereAPosition - SphereBPosition).Normalise();
		t_ColMani.penetrationDepth = t_RadiiSum - t_Distance;
		t_ColMani.contactPointCount = 1;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::S_SphereToSphere(Vector3 sphereAPos, float sphereARadius, Vector3 sphereBPos, float sphereBRadius)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 SphereAPosition = sphereAPos;
	const float SphereARadius = sphereARadius;

	Vector3 SphereBPosition = sphereBPos;
	const float SphereBRadius = sphereBRadius;

	float t_Distance = Vector3(SphereAPosition - SphereBPosition).Magnitude();
	float t_RadiiSum = SphereARadius + SphereBRadius;

	if (t_Distance <= t_RadiiSum)
	{
		t_ColMani.hasCollision = true;
		t_ColMani.collisionNormal = Vector3(SphereAPosition - SphereBPosition).Normalise();
		t_ColMani.penetrationDepth = t_RadiiSum - t_Distance;
		t_ColMani.contactPointCount = 1;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::BoxToBox(GameObjectEntity* boxA, GameObjectEntity* boxB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 BoxAPosition = boxA->m_Transform.m_Position;
	Vector3 BoxBPosition = boxB->m_Transform.m_Position;

	Vector3 t_MaxA = boxA->GetComponent<BoxCollider>()->GetMax();
	Vector3 t_MinA = boxA->GetComponent<BoxCollider>()->GetMin();

	Vector3 t_MaxB = boxB->GetComponent<BoxCollider>()->GetMax();
	Vector3 t_MinB = boxB->GetComponent<BoxCollider>()->GetMin();

	if (t_MinA.x <= t_MaxB.x &&
		t_MaxA.x >= t_MinB.x &&

		t_MinA.y <= t_MaxB.y &&
		t_MaxA.y >= t_MinB.y &&

		t_MinA.z <= t_MaxB.z &&
		t_MaxA.z >= t_MinB.z)
	{
		t_ColMani.hasCollision = true;
		t_ColMani.collisionNormal = Vector3(BoxAPosition - BoxBPosition).Normalise();
		t_ColMani.penetrationDepth = 1 / Vector3(BoxBPosition - BoxAPosition).Magnitude();
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::BoxToSphere(GameObjectEntity* boxA, GameObjectEntity* sphereB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 Nearest = BoxNearestPoint(boxA, sphereB->m_Transform.m_Position);
	float Distance = Nearest.DistanceTo(sphereB->m_Transform.m_Position);

	// Check if the Distance of the Circle is in the Box's "Radius"
	if (Distance <= sphereB->GetComponent<SphereCollider>()->m_Radius)
	{
		t_ColMani.hasCollision = true;
		t_ColMani.collisionNormal = Vector3(sphereB->m_Transform.m_Position - boxA->m_Transform.m_Position).Normalise();
		t_ColMani.penetrationDepth = 0.5;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PlaneToPlane(GameObjectEntity* planeA, GameObjectEntity* planeB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	//Vector3 CrossResult = planeA->GetComponent<PlaneCollider>()->GetNormal().Cross(planeB->GetComponent<PlaneCollider>()->GetNormal());

	//if (CrossResult.Magnitude() > 0 || planeA->m_Transform.m_Position.Magnitude() == planeB->m_Transform.m_Position.Magnitude())
	//{
	//	t_ColMani.hasCollision = true;
	//	t_ColMani.penetrationDepth = 0;
	//	t_ColMani.collisionNormal = Vector3(0, 1, 0);
	//}

	return t_ColMani;
}

CollisionManifold CollisionManager::PlaneToBox(GameObjectEntity* planeA, GameObjectEntity* boxB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	// Vector3 t_Anorm = planeA->GetComponent<PlaneCollider>()->GetNormal().Abs();
	Vector3 t_Anorm = Vector3(0, 1, 0).Abs();
	float t_pLength = boxB->GetComponent<BoxCollider>()->m_Scale.Dot(t_Anorm);
	float t_NormalDot = Vector3(0, 1, 0).Dot(boxB->m_Transform.m_Position);
	float t_Distance = t_NormalDot + planeA->m_Transform.m_Position.Magnitude();

	if (abs(t_Distance) <= t_pLength)
	{
		t_ColMani.hasCollision = true;
		t_ColMani.penetrationDepth = 0.5;
		t_ColMani.collisionNormal = Vector3(0, 1, 0);
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PlaneToSphere(GameObjectEntity* planeA, GameObjectEntity* sphereB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 t_NearPoint = PlaneNearestPoint(planeA, Vector3(0, 1, 0), sphereB->m_Transform.m_Position);
	
	float Distance = t_NearPoint.DistanceTo(sphereB->m_Transform.m_Position);

	if (Distance <= sphereB->GetComponent<SphereCollider>()->m_Radius)
	{
		t_ColMani.hasCollision = true;
		// t_ColMani.collisionNormal = planeA->GetComponent<PlaneCollider>()->GetNormal();
		t_ColMani.collisionNormal = Vector3(0, 1, 0);
		t_ColMani.penetrationDepth = 1 / Vector3(t_NearPoint - sphereB->m_Transform.m_Position).Magnitude();
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::SATtoSAT(GameObjectEntity* satA, GameObjectEntity* satB)
{
	CollisionManifold t_ColMani = CollisionManifold();








	if (true)
	{
		// NOTE: Because SAT does not return the actual penetration depth, we need to aproximate or "make up" what this is
		t_ColMani.hasCollision == true;
		t_ColMani.collisionNormal = Vector3(satA->m_Transform.m_Position - satB->m_Transform.m_Position).Normalise();
		t_ColMani.penetrationDepth = 1 / Vector3(satA->m_Transform.m_Position - satB->m_Transform.m_Position).Magnitude();
	}


	return t_ColMani;
}

bool CollisionManager::CollisionOverlapAxis(GameObjectEntity* satA, GameObjectEntity* boxB, Vector3 axis)
{
	Interval t_A = satA->GetComponent<SATCollider>()->GetInterval(axis);
	Interval t_B = boxB->GetComponent<BoxCollider>()->GetInterval(axis);

	return (t_B.Min <= t_A.Max) && (t_A.Min <= t_B.Max);
}

CollisionManifold CollisionManager::SATtoBox(GameObjectEntity* satA, GameObjectEntity* boxB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 axes[3] = {
		Vector3(1, 0, 0),
		Vector3(0, 1, 0),
		Vector3(0, 0, 1)
	};

	for (int i = 0; i < 3; ++i)
	{
		if (CollisionOverlapAxis(satA, boxB, axes[i]))
		{
			// NOTE: Because SAT does not return the actual penetration depth, we need to aproximate or "make up" what this is
			t_ColMani.hasCollision == true;
			t_ColMani.collisionNormal = Vector3(satA->m_Transform.m_Position - boxB->m_Transform.m_Position).Normalise();
			t_ColMani.penetrationDepth = 1 / Vector3(satA->m_Transform.m_Position - boxB->m_Transform.m_Position).Magnitude();
			break;
		}
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::GJKtoGJK(GameObjectEntity* gjkA, GameObjectEntity* gjkB)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 t_Support = Support(gjkA, gjkB, Vector3(1, 0, 0));
	
	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);
	
	Vector3 t_Direction = -t_Support;
	
	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(gjkA, gjkB, t_Direction);

		float testing = t_Support.Dot(t_Direction);
		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0)
		{ 
			return t_ColMani;
		}
	
		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);
	
		if (NextSimplex(t_Points, t_Direction)) 
		{ 	
			t_ColMani.collisionNormal = Vector3(gjkA->m_Transform.m_Position - gjkB->m_Transform.m_Position).Normalise();
			t_ColMani.penetrationDepth = 1.0f;
			t_ColMani.hasCollision = true;
		 
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::EPAtoEPA(GameObjectEntity* epaA, GameObjectEntity* epaB)
{
	return CollisionManifold();
}

Vector3 CollisionManager::BoxNearestPoint(GameObjectEntity* boxA, Vector3 pointB)
{
	// Min and Max Extents of Box Collider
	const Vector3 t_Max = boxA->GetComponent<BoxCollider>()->GetMax();
	const Vector3 t_Min = boxA->GetComponent<BoxCollider>()->GetMin();

	// Calculating the nearest point
	float t_NearPointX = (pointB.x < t_Min.x) ? t_Min.x : pointB.x;
	float t_NearPointY = (pointB.y < t_Min.y) ? t_Min.y : pointB.y;
	float t_NearPointZ = (pointB.z < t_Min.z) ? t_Min.z : pointB.z;

	// If the nearest point on the axis (x, y, z) are more than the extents, assign the max extent
	t_NearPointX = (t_NearPointX > t_Max.x) ? t_Max.x : t_NearPointX;
	t_NearPointY = (t_NearPointY > t_Max.y) ? t_Max.y : t_NearPointY;
	t_NearPointZ = (t_NearPointZ > t_Max.z) ? t_Max.z : t_NearPointZ;

	// Return final computed video
	return Vector3(t_NearPointX, t_NearPointY, t_NearPointZ);
}

bool CollisionManager::PointInBox(GameObjectEntity* boxA, Vector3 pointB)
{
	const Vector3 t_Max = boxA->GetComponent<BoxCollider>()->GetMax();
	const Vector3 t_Min = boxA->GetComponent<BoxCollider>()->GetMin();

	// Not in Box
	if (pointB.x < t_Min.x || pointB.y < t_Min.y || pointB.z < t_Min.z) { return false; }
	if (pointB.x > t_Max.x || pointB.y > t_Max.y || pointB.z > t_Max.z) { return false; }

	// In Box
	return true;
}

Vector3 CollisionManager::SphereNearestPoint(GameObjectEntity* sphere, Vector3 pointB)
{
	Vector3 t_SphereToPoint = Vector3::S_Normalise(pointB - (sphere->m_Transform.m_Position + sphere->GetComponent<SphereCollider>()->m_Offset));
	t_SphereToPoint *= sphere->GetComponent<SphereCollider>()->m_Radius;
	return t_SphereToPoint + (sphere->m_Transform.m_Position + sphere->GetComponent<SphereCollider>()->m_Offset);
}

bool CollisionManager::PointInSphere(GameObjectEntity* sphere, Vector3 pointB)
{
	float t_MagnitudeSquared = std::pow(Vector3::S_Magnitude(pointB - (sphere->m_Transform.m_Position + sphere->GetComponent<SphereCollider>()->m_Offset)), 2);
	float t_RadiusAmount = sphere->GetComponent<SphereCollider>()->m_Radius * sphere->GetComponent<SphereCollider>()->m_Radius;
	return t_MagnitudeSquared < t_RadiusAmount;
}

Vector3 CollisionManager::PlaneNearestPoint(GameObjectEntity* planeA, Vector3 planeNormal, Vector3 pointB)
{
	float NormalDot = planeNormal.Dot(pointB);
	float t_Distance = NormalDot + planeA->m_Transform.m_Position.Magnitude();
	Vector3 ClosestPoint = planeNormal * t_Distance;
	return pointB - ClosestPoint;
}

bool CollisionManager::PointInPlane(GameObjectEntity* planeA, Vector3 planeNormal, Vector3 pointB)
{
	float t_Dot = Vector3::S_Dot(pointB, planeNormal);
	float t_PlaneDistance = Vector3::S_Magnitude(pointB - planeA->m_Transform.m_Position);
	return t_Dot - t_PlaneDistance == 0.0f;
}
