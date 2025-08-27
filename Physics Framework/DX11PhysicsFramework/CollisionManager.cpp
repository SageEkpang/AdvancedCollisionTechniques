#include "CollisionManager.h"

#include "BoxCollider.h"

CollisionManager::CollisionManager()
{
	m_CollisionMapping[std::make_pair(std::type_index(typeid(SphereCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_SPHERE_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(BoxCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_BOX_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(BoxCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_BOX_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(PlaneCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_PLANE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(SATCollider)), std::type_index(typeid(SATCollider)))] = COLLIDER_TYPE_COLLISIONS_SAT_TO_SAT;
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

		Vector3 closestPointA = BoxNearestPoint(boxA, boxB->m_Transform.m_Position);
		Vector3 closestPointB = BoxNearestPoint(boxB, boxA->m_Transform.m_Position);

		t_ColMani.penetrationDepth = 0.5f;
		t_ColMani.contactPointCount = 1;
	}

	 return t_ColMani;
}

CollisionManifold CollisionManager::BoxToSphere(GameObjectEntity* boxA, GameObjectEntity* sphereB)
{
	//// Sphere Component Variables
	//Vector3 TempPos = other.GetPosition();
	//float TempRadius = other.GetRadius();

	//// Box Component Variables
	//// Centre Position (-+) Extents
	//m_Max = m_Transform->GetPosition() + m_Transform->GetScale();
	//m_Min = m_Transform->GetPosition() - m_Transform->GetScale();

	//// Minimum Distance Temp Variable
	//float DistanceMin = 0;

	//// Check the Distance of the Circle Position from the Box position and extents
	//if (TempPos.x < m_Min.x) DistanceMin += std::powf(TempPos.x - m_Min.x, 2);
	//else if (TempPos.x > m_Max.x) DistanceMin += std::powf(TempPos.x - m_Max.x, 2);

	//if (TempPos.y < m_Min.y) DistanceMin += std::powf(TempPos.y - m_Min.y, 2);
	//else if (TempPos.y > m_Max.y) DistanceMin += std::powf(TempPos.y - m_Max.y, 2);

	//if (TempPos.z < m_Min.z) DistanceMin += std::powf(TempPos.z - m_Min.z, 2);
	//else if (TempPos.z > m_Max.z) DistanceMin += std::powf(TempPos.z - m_Max.z, 2);

	//// Check if the Distance of the Circle is in the Box's "Radius"
	//if (DistanceMin <= (std::powf(TempRadius, 2)))
	//{
	//	out.CollisionNormal = Vector::Normalise(other.GetPosition() - m_Transform->GetPosition());
	//	out.CollisionNormal = Vector::Normalise(out.CollisionNormal);
	//	return true;
	//}

	//return false;






	return CollisionManifold();
}

CollisionManifold CollisionManager::PlaneToPlane(GameObjectEntity* planeA, GameObjectEntity* planeB)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::PlaneToBox(GameObjectEntity* planeA, GameObjectEntity* boxB)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::PlaneToSphere(GameObjectEntity* planeA, GameObjectEntity* sphereB)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::SATtoSAT(GameObjectEntity* satA, GameObjectEntity* satB)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::GJKtoGJK(GameObjectEntity* gjkA, GameObjectEntity* gjkB)
{
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
	t_SphereToPoint *= sphere->GetComponent<SphereCollider>()->m_Radius;// *float((sphere->m_Transform.m_Scale.x + sphere->m_Transform.m_Scale.y + sphere->m_Transform.m_Scale.z) / 3.0f);
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
	float NormalDot = Vector3::S_Dot(planeNormal, pointB);
	float t_Distance = NormalDot - Vector3::S_Magnitude(pointB - planeA->m_Transform.m_Position);
	Vector3 ClosestPoint = pointB - Vector3(0, 1, 0) * t_Distance;
	return ClosestPoint;
}

bool CollisionManager::PointInPlane(GameObjectEntity* planeA, Vector3 planeNormal, Vector3 pointB)
{
	float t_Dot = Vector3::S_Dot(pointB, planeNormal);
	float t_PlaneDistance = Vector3::S_Magnitude(pointB - planeA->m_Transform.m_Position);
	return t_Dot - t_PlaneDistance == 0.0f;
}
