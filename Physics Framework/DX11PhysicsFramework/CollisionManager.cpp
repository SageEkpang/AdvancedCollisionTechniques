#include "CollisionManager.h"

// EPA
void CollisionManager::AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t>& faces, size_t a, size_t b)
{
	// NOTE: Checks if the reverse of the edge already exists in the list, if so, remove said list
	auto t_Reverse = std::find(edges.begin(), edges.end(), std::make_pair(faces[b], faces[a]));
	
	if (t_Reverse != edges.end())
	{
		edges.erase(t_Reverse);
	}
	else
	{
		edges.emplace_back(faces[a], faces[b]);
	}
}

std::pair<std::vector<Vector4>, size_t> CollisionManager::GetFaceNormals(std::vector<Vector3>& polytope, std::vector<size_t>& faces)
{
	//	// NOTE: Get the Array of Normal Faces
	std::vector<Vector4> t_NormalArray;
	size_t t_MinTriangle = 0;
	float t_MinDistance = FLT_MAX;

	for (size_t i = 0; i < faces.size(); i += 3)
	{
		Vector3 t_A = polytope[faces[i    ]];
		Vector3 t_B = polytope[faces[i + 1]];
		Vector3 t_C = polytope[faces[i + 2]];

		Vector3 t_Normal = Vector3::S_Normalise(Vector3::S_Cross(t_B - t_A, t_C - t_A));
		float t_Distance = Vector3::S_Dot(t_Normal, t_A);

		if (t_Distance < 0)
		{
			t_Normal *= -1;
			t_Distance *= -1;
		}

		Vector4 t_TempNorm = Vector4(t_Normal.x, t_Normal.y, t_Normal.z, t_Distance);
		t_NormalArray.emplace_back(t_TempNorm);

		if (t_Distance < t_MinDistance)
		{
			t_MinTriangle = i / 3;
			t_MinDistance = t_Distance;
		}
	}

	return { t_NormalArray, t_MinTriangle};
}

bool CollisionManager::Line(Simplex& points, Vector3& direction)
{
	// NOTE: Check if the Point Ever Intersects the Line at All
	Vector3 t_A = points[0];
	Vector3 t_B = points[1];

	Vector3 t_AB = t_B - t_A;
	Vector3 t_AO = -t_A;

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

Vector3 CollisionManager::FindFurthestPoint(GameObjectEntity* colliderA, Vector3 direction)
{

	// STEP 1: Find the Max Point
	Vector3 t_MaxPoint;
	float t_MaxDistance = -FLT_MAX;

	// NOTE: Find furthest vertex
	for (Vector3& v : colliderA->FindChildComponent<ColliderEntity>()->m_PositionStore)
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

CollisionManager::CollisionManager()
{
	m_CollisionMapping[std::make_pair(std::type_index(typeid(SphereCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_SPHERE_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(BoxCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_BOX_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(BoxCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_BOX_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(PlaneCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_PLANE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(PlaneCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_PLANE_TO_SPHERE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(RayCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_RAY_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(RayCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_RAY_TO_SPHERE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(RayCollider)), std::type_index(typeid(PlaneCollider)))] = COLLIDER_TYPE_COLLISIONS_RAY_TO_PLANE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(RayCollider)), std::type_index(typeid(EPACollider)))] = COLLIDER_TYPE_COLLISIONS_RAY_TO_EPA;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(RayCollider)), std::type_index(typeid(GJKCollider)))] = COLLIDER_TYPE_COLLISIONS_RAY_TO_GJK;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(RayCollider)), std::type_index(typeid(MassAggregate)))] = COLLIDER_TYPE_COLLISIONS_RAY_TO_MASS_AGG;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(SATCollider)), std::type_index(typeid(SATCollider)))] = COLLIDER_TYPE_COLLISIONS_SAT_TO_SAT;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(SATCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_SAT_TO_BOX;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(EPACollider)), std::type_index(typeid(EPACollider)))] = COLLIDER_TYPE_COLLISIONS_EPA_TO_EPA;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(EPACollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_EPA_TO_SPHERE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(EPACollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_EPA_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(EPACollider)), std::type_index(typeid(PlaneCollider)))] = COLLIDER_TYPE_COLLISIONS_EPA_TO_PLANE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(EPACollider)), std::type_index(typeid(GJKCollider)))] = COLLIDER_TYPE_COLLISIONS_EPA_TO_GJK;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(GJKCollider)), std::type_index(typeid(GJKCollider)))] = COLLIDER_TYPE_COLLISIONS_GJK_TO_GJK;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(GJKCollider)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_GJK_TO_SPHERE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(GJKCollider)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_GJK_TO_BOX;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(GJKCollider)), std::type_index(typeid(PlaneCollider)))] = COLLIDER_TYPE_COLLISIONS_GJK_TO_PLANE;

	m_CollisionMapping[std::make_pair(std::type_index(typeid(MassAggregate)), std::type_index(typeid(SphereCollider)))] = COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_SPHERE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(MassAggregate)), std::type_index(typeid(PlaneCollider)))] = COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_PLANE;
	m_CollisionMapping[std::make_pair(std::type_index(typeid(MassAggregate)), std::type_index(typeid(BoxCollider)))] = COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_BOX;
}

CollisionManager::~CollisionManager()
{
	m_CollisionMapping.clear();
}

CollisionManifold CollisionManager::CheckCollisions(GameObjectEntity* colliderA, GameObjectEntity* colliderB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	// NOTE: Temp Collision Variables
	GameObjectEntity* tempA = nullptr;
	GameObjectEntity* tempB = nullptr;

	// NOTE: Check if the collider component exists within the game object
	if (colliderA->FindChildComponent<ColliderEntity>()) { tempA = colliderA; }
	if (colliderB->FindChildComponent<ColliderEntity>()) { tempB = colliderB; }
	if (tempA == nullptr || tempB == nullptr) { return CollisionManifold(); }

	if (tempA->FindChildComponent<ColliderEntity>()->m_IsCollideable == false ||
		tempB->FindChildComponent<ColliderEntity>()->m_IsCollideable == false)
	{
		return CollisionManifold();
	}

	// NOTE: Assign the static casted class to the Game Objects
	auto collision_made_pair = std::make_pair(tempA->FindChildComponentID<ColliderEntity>(), tempB->FindChildComponentID<ColliderEntity>());
	auto collision_solution_pair = std::make_pair(tempA, tempB);
	auto collision_solution_pair_flip = std::make_pair(tempB, tempA);

	// NOTE: Check if it exists in the Map Already
	if (!collisionSolutionMap.count(collision_solution_pair) == 0) { return CollisionManifold(); }
	if (!collisionSolutionMap.count(collision_solution_pair_flip) == 0) { return CollisionManifold(); }

	// NOTE: Reverse pair if it is not within the collision map
	if (m_CollisionMapping.count(collision_made_pair) == 0)
	{
		std::swap(collision_made_pair.first, collision_made_pair.second);
		std::swap(tempA, tempB);
	}

	switch (m_CollisionMapping[collision_made_pair])
	{
		case COLLIDER_TYPE_COLLISIONS_SPHERE_TO_SPHERE: return SphereToSphere(tempA, tempB, collisionSolutionMap); break;
		
		case COLLIDER_TYPE_COLLISIONS_BOX_TO_BOX: return BoxToBox(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_BOX_TO_SPHERE: return BoxToSphere(tempA, tempB, collisionSolutionMap); break;

		case COLLIDER_TYPE_COLLISIONS_PLANE_TO_PLANE: return PlaneToPlane(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_PLANE_TO_BOX: return PlaneToBox(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_PLANE_TO_SPHERE: return PlaneToSphere(tempA, tempB, collisionSolutionMap); break;

		case COLLIDER_TYPE_COLLISIONS_RAY_TO_BOX: return RayToBox(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_RAY_TO_SPHERE: return RayToSphere(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_RAY_TO_PLANE: return RayToPlane(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_RAY_TO_EPA: return RayToEPA(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_RAY_TO_GJK: return RayToGJK(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_RAY_TO_MASS_AGG: return RayToMassAgg(tempA, tempB, collisionSolutionMap); break;

		case COLLIDER_TYPE_COLLISIONS_SAT_TO_SAT: return SATtoSAT(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_SAT_TO_BOX: return SATtoBox(tempA, tempB, collisionSolutionMap); break;

		case COLLIDER_TYPE_COLLISIONS_EPA_TO_EPA: return EPAtoEPA(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_EPA_TO_SPHERE: return EPAtoSphere(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_EPA_TO_BOX: return EPAtoBox(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_EPA_TO_PLANE: return EPAtoPlane(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_EPA_TO_GJK: return EPAtoGJK(tempA, tempB, collisionSolutionMap); break;

		case COLLIDER_TYPE_COLLISIONS_GJK_TO_GJK: return GJKtoGJK(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_GJK_TO_SPHERE: return GJKtoSphere(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_GJK_TO_BOX: return GJKtoBox(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_GJK_TO_PLANE: return GJKtoPlane(tempA, tempB, collisionSolutionMap); break;

		case COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_MASS_AGG: return MassAggToMassAgg(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_SPHERE: return MassAggToSphere(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_PLANE: return MassAggToPlane(tempA, tempB, collisionSolutionMap); break;
		case COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_BOX: return MassAggToBox(tempA, tempB, collisionSolutionMap); break;

		default: break;
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::SphereToSphere(GameObjectEntity* sphereA, GameObjectEntity* sphereB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
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

		collisionSolutionMap[std::make_pair(sphereA, sphereB)] = t_ColMani;
		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::BoxToBox(GameObjectEntity* boxA, GameObjectEntity* boxB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
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
		t_ColMani.penetrationDepth = 1 / Vector3(BoxAPosition - BoxBPosition).Magnitude();

		collisionSolutionMap[std::make_pair(boxA, boxB)] = t_ColMani;
		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::BoxToSphere(GameObjectEntity* boxA, GameObjectEntity* sphereB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 Nearest = BoxNearestPoint(boxA, sphereB->m_Transform.m_Position);
	float Distance = Nearest.DistanceTo(sphereB->m_Transform.m_Position);

	// Check if the Distance of the Circle is in the Box's "Radius"
	if (Distance <= sphereB->GetComponent<SphereCollider>()->m_Radius)
	{
		t_ColMani.hasCollision = true;
		t_ColMani.collisionNormal = Vector3(sphereB->m_Transform.m_Position - Nearest).Normalise();
		t_ColMani.penetrationDepth = sphereB->GetComponent<SphereCollider>()->m_Radius - Vector3(Nearest - sphereB->m_Transform.m_Position).Magnitude();

		collisionSolutionMap[std::make_pair(sphereB, boxA)] = t_ColMani;
		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PlaneToPlane(GameObjectEntity* planeA, GameObjectEntity* planeB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
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

CollisionManifold CollisionManager::PlaneToBox(GameObjectEntity* planeA, GameObjectEntity* boxB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
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
		t_ColMani.collisionNormal = Vector3(0, 1, 0);
		t_ColMani.penetrationDepth = t_pLength - Vector3(PlaneNearestPoint(planeA, Vector3(0, 1, 0), boxB->m_Transform.m_Position) - boxB->m_Transform.m_Position).Magnitude();

		collisionSolutionMap[std::make_pair(boxB, planeA)] = t_ColMani;
		return t_ColMani;
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::PlaneToSphere(GameObjectEntity* planeA, GameObjectEntity* sphereB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 t_NearPoint = PlaneNearestPoint(planeA, Vector3(0, 1, 0), sphereB->m_Transform.m_Position);
	float Distance = t_NearPoint.DistanceTo(sphereB->m_Transform.m_Position);

	if (Distance <= sphereB->GetComponent<SphereCollider>()->m_Radius)
	{
		t_ColMani.hasCollision = true;
		// t_ColMani.collisionNormal = planeA->GetComponent<PlaneCollider>()->GetNormal();
		t_ColMani.collisionNormal = Vector3(0, 1, 0);
		t_ColMani.penetrationDepth = sphereB->GetComponent<SphereCollider>()->m_Radius - Vector3(t_NearPoint - sphereB->m_Transform.m_Position).Magnitude();

		collisionSolutionMap[std::make_pair(sphereB, planeA)] = t_ColMani;
		return t_ColMani;
	}
	
	return t_ColMani;
}

CollisionManifold CollisionManager::RayToBox(GameObjectEntity* rayA, GameObjectEntity* boxB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 min = boxB->GetComponent<BoxCollider>()->GetMin();
	Vector3 max = boxB->GetComponent<BoxCollider>()->GetMax();

	float t1 = (min.x - rayA->GetComponent<RayCollider>()->m_Origin.x) / rayA->GetComponent<RayCollider>()->m_Direction.Normalise().x;
	float t2 = (max.x - rayA->GetComponent<RayCollider>()->m_Origin.x) / rayA->GetComponent<RayCollider>()->m_Direction.Normalise().x;
	float t3 = (min.y - rayA->GetComponent<RayCollider>()->m_Origin.y) / rayA->GetComponent<RayCollider>()->m_Direction.Normalise().y;
	float t4 = (max.y - rayA->GetComponent<RayCollider>()->m_Origin.y) / rayA->GetComponent<RayCollider>()->m_Direction.Normalise().y;
	float t5 = (min.z - rayA->GetComponent<RayCollider>()->m_Origin.z) / rayA->GetComponent<RayCollider>()->m_Direction.Normalise().z;
	float t6 = (max.z - rayA->GetComponent<RayCollider>()->m_Origin.z) / rayA->GetComponent<RayCollider>()->m_Direction.Normalise().z;

	float tmin = fmaxf(
		fmaxf(
			fminf(t1, t2),
			fminf(t3, t4)
		),
		fminf(t5, t6)
	);

	float tmax = fminf(
		fminf(
			fmaxf(t1, t2),
			fmaxf(t3, t4)
		),
		fmaxf(t5, t6)
	);

	if (tmax < 0) {
		return CollisionManifold();
	}

	if (tmin > tmax) {
		return CollisionManifold();
	}

	if (tmin < 0.0f) 
	{
		t_ColMani.hasCollision = true;
		t_ColMani.ownerObject = rayA;
		t_ColMani.hitObject = boxB;
		t_ColMani.origin = rayA->GetComponent<RayCollider>()->m_Origin;
		t_ColMani.direction = rayA->GetComponent<RayCollider>()->m_Direction;

		return t_ColMani;
	}

	t_ColMani.hasCollision = true;
	t_ColMani.ownerObject = rayA;
	t_ColMani.hitObject = boxB;
	t_ColMani.origin = rayA->GetComponent<RayCollider>()->m_Origin;
	t_ColMani.direction = rayA->GetComponent<RayCollider>()->m_Direction;

	return t_ColMani;
}

CollisionManifold CollisionManager::RayToSphere(GameObjectEntity* rayA, GameObjectEntity* sphereB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 t_M = rayA->GetComponent<RayCollider>()->m_Origin - sphereB->m_Transform.m_Position;
	float t_B = Vector3::S_Dot(t_M, rayA->GetComponent<RayCollider>()->m_Direction);
	float t_C = Vector3::S_Dot(t_M, t_M) - (sphereB->GetComponent<SphereCollider>()->m_Radius * sphereB->GetComponent<SphereCollider>()->m_Radius);

	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0) 
	if (t_C > 0.0f && t_B > 0.0f) return CollisionManifold();
	float discr = t_B * t_B - t_C;

	// A negative discriminant corresponds to ray missing sphere 
	if (discr < 0.0f) return CollisionManifold();

	t_ColMani.hasCollision = true;
	t_ColMani.ownerObject = rayA;
	t_ColMani.hitObject = sphereB;
	t_ColMani.origin = rayA->GetComponent<RayCollider>()->m_Origin;
	t_ColMani.direction = rayA->GetComponent<RayCollider>()->m_Direction;

	return t_ColMani;
}

CollisionManifold CollisionManager::RayToPlane(GameObjectEntity* rayA, GameObjectEntity* planeB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani;

	//float t_ND = Vector3::S_Dot(rayA->GetComponent<RayCollider>()->m_Direction, Vector3(0, 1, 0));
	//float t_PN = Vector3::S_Dot(rayA->GetComponent<RayCollider>()->m_Origin, Vector3(0, 1, 0));

	//if (t_ND >= 0.0f) { return CollisionManifold(); }

	//float t_T = (planeB->m_Transform.m_Position.Magnitude() - t_PN) / t_ND;

	//if (t_T >= 0.0f)
	//{
	//	t_ColMani.hasCollision = true;
	//	t_ColMani.ownerObject = rayA;
	//	t_ColMani.hitObject = planeB;
	//	t_ColMani.origin = rayA->GetComponent<RayCollider>()->m_Origin;
	//	t_ColMani.direction = rayA->GetComponent<RayCollider>()->m_Direction;
	//	return t_ColMani;
	//}

	return CollisionManifold();
}

CollisionManifold CollisionManager::RayToEPA(GameObjectEntity* rayA, GameObjectEntity* epaB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{


	return CollisionManifold();
}

CollisionManifold CollisionManager::RayToGJK(GameObjectEntity* rayA, GameObjectEntity* gjkB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{

	return CollisionManifold();
}

CollisionManifold CollisionManager::RayToMassAgg(GameObjectEntity* rayA, GameObjectEntity* massAggB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani;

	for (int i = 0; i < massAggB->GetComponent<MassAggregate>()->m_MassPoints.size(); ++i)
	{
		const float t_MassAggRadius = massAggB->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius;

		Vector3 t_M = rayA->GetComponent<RayCollider>()->m_Origin - massAggB->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position;
		float t_B = Vector3::S_Dot(t_M, rayA->GetComponent<RayCollider>()->m_Direction);
		float t_C = Vector3::S_Dot(t_M, t_M) - (massAggB->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius * massAggB->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius);

		// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0) 
		if (t_C > 0.0f && t_B > 0.0f) { continue; }

		float discr = t_B * t_B - t_C;

		// A negative discriminant corresponds to ray missing sphere 
		if (discr < 0.0f) { continue; }

		t_ColMani.hasCollision = true;
		t_ColMani.ownerObject = rayA;
		t_ColMani.hitObject = massAggB->GetComponent<MassAggregate>()->m_MassPoints[i];
		t_ColMani.origin = rayA->GetComponent<RayCollider>()->m_Origin;
		t_ColMani.direction = rayA->GetComponent<RayCollider>()->m_Direction;

		return t_ColMani;
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::SATtoSAT(GameObjectEntity* satA, GameObjectEntity* satB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();








	if (true)
	{
		// NOTE: Because SAT does not return the actual penetration depth, we need to aproximate or "make up" what this is
		t_ColMani.hasCollision = true;
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

CollisionManifold CollisionManager::SATtoBox(GameObjectEntity* satA, GameObjectEntity* boxB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
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
			t_ColMani.hasCollision = true;
			t_ColMani.collisionNormal = Vector3(satA->m_Transform.m_Position - boxB->m_Transform.m_Position).Normalise();
			t_ColMani.penetrationDepth = 1 / Vector3(satA->m_Transform.m_Position - boxB->m_Transform.m_Position).Magnitude();

			collisionSolutionMap[std::make_pair(satA, boxB)] = t_ColMani;

			break;
		}
	}

	return t_ColMani;
}

CollisionManifold CollisionManager::GJKtoGJK(GameObjectEntity* gjkA, GameObjectEntity* gjkB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
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

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0)
		{ 
			return CollisionManifold();
		}
	
		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);
	
		if (NextSimplex(t_Points, t_Direction)) 
		{ 	
			t_ColMani.collisionNormal = Vector3(gjkA->m_Transform.m_Position - gjkB->m_Transform.m_Position).Normalise();
			t_ColMani.penetrationDepth = 0.2f;
			t_ColMani.hasCollision = true;

			collisionSolutionMap[std::make_pair(gjkA, gjkB)] = t_ColMani;
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::GJKtoSphere(GameObjectEntity* gjkA, GameObjectEntity* sphereB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 t_Support = Support(gjkA, sphereB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(gjkA, sphereB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0)
		{
			return CollisionManifold();
		}

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction))
		{
			t_ColMani.collisionNormal = Vector3(gjkA->m_Transform.m_Position - sphereB->m_Transform.m_Position).Normalise();
			t_ColMani.penetrationDepth = 0.2f;
			t_ColMani.hasCollision = true;

			collisionSolutionMap[std::make_pair(gjkA, sphereB)] = t_ColMani;
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::GJKtoBox(GameObjectEntity* gjkA, GameObjectEntity* boxB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 t_Support = Support(gjkA, boxB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(gjkA, boxB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0)
		{
			return CollisionManifold();
		}

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction))
		{
			t_ColMani.collisionNormal = Vector3(gjkA->m_Transform.m_Position - boxB->m_Transform.m_Position).Normalise();
			t_ColMani.penetrationDepth = 0.2f;
			t_ColMani.hasCollision = true;

			collisionSolutionMap[std::make_pair(gjkA, boxB)] = t_ColMani;
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::GJKtoPlane(GameObjectEntity* gjkA, GameObjectEntity* planeB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	Vector3 t_Support = Support(gjkA, planeB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(gjkA, planeB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0)
		{
			return CollisionManifold();
		}

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction))
		{
			t_ColMani.collisionNormal = Vector3(0, 1, 0);
			t_ColMani.penetrationDepth = 0.2f;
			t_ColMani.hasCollision = true;

			collisionSolutionMap[std::make_pair(gjkA, planeB)] = t_ColMani;
			return t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::EPAtoEPA(GameObjectEntity* epaA, GameObjectEntity* epaB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();
	Simplex t_OutSimplex = Simplex();

	// NOTE: Normal GJK Algorithm
	Vector3 t_Support = Support(epaA, epaB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	// NOTE: Run the GJK Algorithm and Break Out the loop when a simplex is found and store the outsimplex in the out simplex structure
	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(epaA, epaB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0) { return CollisionManifold(); }

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction)) { t_OutSimplex = t_Points; break; }
	}


	// NOTE: EPA (Expanding Poltyope Algorithm) Begin
	std::vector<Vector3> t_Polytope(t_OutSimplex.begin(), t_OutSimplex.end());

	// NOTE: Potential Face / Triangle list, in terms of Winding order
	std::vector<size_t> t_Faces = {

		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	// NOTE: n-Polytope of the face, Minimum face normal
	// NOTE: Calculates the new normals of the Face
	auto [t_Normals, t_MinFace] = GetFaceNormals(t_Polytope, t_Faces);

	Vector3 t_MinimumNormal;
	float t_MinimumDistance = FLT_MAX;

	while (t_MinimumDistance == FLT_MAX)
	{
		t_MinimumNormal = t_Normals[t_MinFace].xyz();
		t_MinimumDistance = t_Normals[t_MinFace].w;

		t_Support = Support(epaA, epaB, t_MinimumNormal);
		float t_Distance = Vector3::S_Dot(t_MinimumNormal, t_Support);

		// NOTE: Calculate the Distance to see if the normal face is within range of the point
		if (abs(t_Distance - t_MinimumDistance) > 0.001f)
		{
			t_MinimumDistance = FLT_MAX;
			std::vector<std::pair<size_t, size_t>> t_UniqueEdges;

			for (int i = 0; i < t_Normals.size(); i++)
			{
				if ((Vector3::S_Dot(t_Normals[i].xyz(), t_Support) - t_Normals[i].w) > 0)
				{
					size_t t_F = i * 3;

					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F,     t_F + 1);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 1, t_F + 2);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 2, t_F);

					t_Faces[t_F + 2] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F + 1] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F    ] = t_Faces.back(); t_Faces.pop_back();

					t_Normals[i] = t_Normals.back();
					t_Normals.pop_back();

					i--;
				}
			}

			// NOTE: Work out if the New Faces and the Unique Edges match
			std::vector<size_t> t_NewFaces;
			for (auto [edgeIndex1, edgeIndex2] : t_UniqueEdges)
			{
				t_NewFaces.push_back(edgeIndex1);
				t_NewFaces.push_back(edgeIndex2);
				t_NewFaces.push_back(t_Polytope.size());
			}

			t_Polytope.push_back(t_Support);

			auto [t_NewNormals, t_NewMinimumFace] = GetFaceNormals(t_Polytope, t_NewFaces);

			// NOTE: Check if the Normal is within the distance from the old distance to calculate the normal distance
			float t_OldMinDistance = FLT_MAX;
			for (size_t i = 0; i < t_Normals.size(); i++)
			{
				if (t_Normals[i].w < t_OldMinDistance)
				{
					t_OldMinDistance = t_Normals[i].w;
					t_MinFace = i;
				}
			}

			if (t_NewNormals[t_NewMinimumFace].w < t_OldMinDistance)
			{
				t_MinFace = t_NewMinimumFace + t_Normals.size();
			}

			t_Faces  .insert(t_Faces  .end(), t_NewFaces  .begin(), t_NewFaces  .end());
			t_Normals.insert(t_Normals.end(), t_NewNormals.begin(), t_NewNormals.end());
		}
	}

	t_ColMani.collisionNormal = -1 * (t_MinimumNormal.Normalise());
	t_ColMani.penetrationDepth = t_MinimumDistance + 0.01f;
	t_ColMani.hasCollision = true;

	collisionSolutionMap[std::make_pair(epaA, epaB)] = t_ColMani;
	return t_ColMani;
}

CollisionManifold CollisionManager::EPAtoSphere(GameObjectEntity* epaA, GameObjectEntity* sphereB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();
	Simplex t_OutSimplex = Simplex();

	// NOTE: Normal GJK Algorithm
	Vector3 t_Support = Support(epaA, sphereB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	// NOTE: Run the GJK Algorithm and Break Out the loop when a simplex is found and store the outsimplex in the out simplex structure
	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(epaA, sphereB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0) { return CollisionManifold(); }

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction)) { t_OutSimplex = t_Points; break; }
	}


	// NOTE: EPA (Expanding Poltyope Algorithm) Begin
	std::vector<Vector3> t_Polytope(t_OutSimplex.begin(), t_OutSimplex.end());

	// NOTE: Potential Face / Triangle list, in terms of Winding order
	std::vector<size_t> t_Faces = {

		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	// NOTE: n-Polytope of the face, Minimum face normal
	// NOTE: Calculates the new normals of the Face
	auto [t_Normals, t_MinFace] = GetFaceNormals(t_Polytope, t_Faces);

	Vector3 t_MinimumNormal;
	float t_MinimumDistance = FLT_MAX;

	while (t_MinimumDistance == FLT_MAX)
	{
		t_MinimumNormal = t_Normals[t_MinFace].xyz();
		t_MinimumDistance = t_Normals[t_MinFace].w;

		t_Support = Support(epaA, sphereB, t_MinimumNormal);
		float t_Distance = Vector3::S_Dot(t_MinimumNormal, t_Support);

		// NOTE: Calculate the Distance to see if the normal face is within range of the point
		if (abs(t_Distance - t_MinimumDistance) > 0.001f)
		{
			t_MinimumDistance = FLT_MAX;
			std::vector<std::pair<size_t, size_t>> t_UniqueEdges;

			for (int i = 0; i < t_Normals.size(); i++)
			{
				if ((Vector3::S_Dot(t_Normals[i].xyz(), t_Support) - t_Normals[i].w) > 0)
				{
					size_t t_F = i * 3;

					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F, t_F + 1);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 1, t_F + 2);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 2, t_F);

					t_Faces[t_F + 2] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F + 1] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F] = t_Faces.back(); t_Faces.pop_back();

					t_Normals[i] = t_Normals.back();
					t_Normals.pop_back();

					i--;
				}
			}

			// NOTE: Work out if the New Faces and the Unique Edges match
			std::vector<size_t> t_NewFaces;
			for (auto [edgeIndex1, edgeIndex2] : t_UniqueEdges)
			{
				t_NewFaces.push_back(edgeIndex1);
				t_NewFaces.push_back(edgeIndex2);
				t_NewFaces.push_back(t_Polytope.size());
			}

			t_Polytope.push_back(t_Support);

			auto [t_NewNormals, t_NewMinimumFace] = GetFaceNormals(t_Polytope, t_NewFaces);

			// NOTE: Check if the Normal is within the distance from the old distance to calculate the normal distance
			float t_OldMinDistance = FLT_MAX;
			for (size_t i = 0; i < t_Normals.size(); i++)
			{
				if (t_Normals[i].w < t_OldMinDistance)
				{
					t_OldMinDistance = t_Normals[i].w;
					t_MinFace = i;
				}
			}

			if (t_NewNormals[t_NewMinimumFace].w < t_OldMinDistance)
			{
				t_MinFace = t_NewMinimumFace + t_Normals.size();
			}

			t_Faces.insert(t_Faces.end(), t_NewFaces.begin(), t_NewFaces.end());
			t_Normals.insert(t_Normals.end(), t_NewNormals.begin(), t_NewNormals.end());
		}
	}

	t_ColMani.collisionNormal = -1 * (t_MinimumNormal.Normalise());
	t_ColMani.penetrationDepth = t_MinimumDistance + 0.01f;
	t_ColMani.hasCollision = true;

	collisionSolutionMap[std::make_pair(epaA, sphereB)] = t_ColMani;
	return t_ColMani;
}

CollisionManifold CollisionManager::EPAtoBox(GameObjectEntity* epaA, GameObjectEntity* boxB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();
	Simplex t_OutSimplex = Simplex();

	// NOTE: Normal GJK Algorithm
	Vector3 t_Support = Support(epaA, boxB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	// NOTE: Run the GJK Algorithm and Break Out the loop when a simplex is found and store the outsimplex in the out simplex structure
	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(epaA, boxB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0) { return CollisionManifold(); }

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction)) { t_OutSimplex = t_Points; break; }
	}


	// NOTE: EPA (Expanding Poltyope Algorithm) Begin
	std::vector<Vector3> t_Polytope(t_OutSimplex.begin(), t_OutSimplex.end());

	// NOTE: Potential Face / Triangle list, in terms of Winding order
	std::vector<size_t> t_Faces = {

		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	// NOTE: n-Polytope of the face, Minimum face normal
	// NOTE: Calculates the new normals of the Face
	auto [t_Normals, t_MinFace] = GetFaceNormals(t_Polytope, t_Faces);

	Vector3 t_MinimumNormal;
	float t_MinimumDistance = FLT_MAX;

	while (t_MinimumDistance == FLT_MAX)
	{
		t_MinimumNormal = t_Normals[t_MinFace].xyz();
		t_MinimumDistance = t_Normals[t_MinFace].w;

		t_Support = Support(epaA, boxB, t_MinimumNormal);
		float t_Distance = Vector3::S_Dot(t_MinimumNormal, t_Support);

		// NOTE: Calculate the Distance to see if the normal face is within range of the point
		if (abs(t_Distance - t_MinimumDistance) > 0.001f)
		{
			t_MinimumDistance = FLT_MAX;
			std::vector<std::pair<size_t, size_t>> t_UniqueEdges;

			for (int i = 0; i < t_Normals.size(); i++)
			{
				if ((Vector3::S_Dot(t_Normals[i].xyz(), t_Support) - t_Normals[i].w) > 0)
				{
					size_t t_F = i * 3;

					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F, t_F + 1);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 1, t_F + 2);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 2, t_F);

					t_Faces[t_F + 2] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F + 1] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F] = t_Faces.back(); t_Faces.pop_back();

					t_Normals[i] = t_Normals.back();
					t_Normals.pop_back();

					i--;
				}
			}

			// NOTE: Work out if the New Faces and the Unique Edges match
			std::vector<size_t> t_NewFaces;
			for (auto [edgeIndex1, edgeIndex2] : t_UniqueEdges)
			{
				t_NewFaces.push_back(edgeIndex1);
				t_NewFaces.push_back(edgeIndex2);
				t_NewFaces.push_back(t_Polytope.size());
			}

			t_Polytope.push_back(t_Support);

			auto [t_NewNormals, t_NewMinimumFace] = GetFaceNormals(t_Polytope, t_NewFaces);

			// NOTE: Check if the Normal is within the distance from the old distance to calculate the normal distance
			float t_OldMinDistance = FLT_MAX;
			for (size_t i = 0; i < t_Normals.size(); i++)
			{
				if (t_Normals[i].w < t_OldMinDistance)
				{
					t_OldMinDistance = t_Normals[i].w;
					t_MinFace = i;
				}
			}

			if (t_NewNormals[t_NewMinimumFace].w < t_OldMinDistance)
			{
				t_MinFace = t_NewMinimumFace + t_Normals.size();
			}

			t_Faces.insert(t_Faces.end(), t_NewFaces.begin(), t_NewFaces.end());
			t_Normals.insert(t_Normals.end(), t_NewNormals.begin(), t_NewNormals.end());
		}
	}

	t_ColMani.collisionNormal = -1 * (t_MinimumNormal.Normalise());
	t_ColMani.penetrationDepth = t_MinimumDistance + 0.01f;
	t_ColMani.hasCollision = true;

	collisionSolutionMap[std::make_pair(epaA, boxB)] = t_ColMani;
	return t_ColMani;
}

CollisionManifold CollisionManager::EPAtoPlane(GameObjectEntity* epaA, GameObjectEntity* planeB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();
	Simplex t_OutSimplex = Simplex();

	// NOTE: Normal GJK Algorithm
	Vector3 t_Support = Support(epaA, planeB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	// NOTE: Run the GJK Algorithm and Break Out the loop when a simplex is found and store the outsimplex in the out simplex structure
	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(epaA, planeB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0) { return CollisionManifold(); }

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction)) { t_OutSimplex = t_Points; break; }
	}


	// NOTE: EPA (Expanding Poltyope Algorithm) Begin
	std::vector<Vector3> t_Polytope(t_OutSimplex.begin(), t_OutSimplex.end());

	// NOTE: Potential Face / Triangle list, in terms of Winding order
	std::vector<size_t> t_Faces = {

		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	// NOTE: n-Polytope of the face, Minimum face normal
	// NOTE: Calculates the new normals of the Face
	auto [t_Normals, t_MinFace] = GetFaceNormals(t_Polytope, t_Faces);

	Vector3 t_MinimumNormal;
	float t_MinimumDistance = FLT_MAX;

	while (t_MinimumDistance == FLT_MAX)
	{
		t_MinimumNormal = t_Normals[t_MinFace].xyz();
		t_MinimumDistance = t_Normals[t_MinFace].w;

		t_Support = Support(epaA, planeB, t_MinimumNormal);
		float t_Distance = Vector3::S_Dot(t_MinimumNormal, t_Support);

		// NOTE: Calculate the Distance to see if the normal face is within range of the point
		if (abs(t_Distance - t_MinimumDistance) > 0.001f)
		{
			t_MinimumDistance = FLT_MAX;
			std::vector<std::pair<size_t, size_t>> t_UniqueEdges;

			for (int i = 0; i < t_Normals.size(); i++)
			{
				if ((Vector3::S_Dot(t_Normals[i].xyz(), t_Support) - t_Normals[i].w) > 0)
				{
					size_t t_F = i * 3;

					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F, t_F + 1);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 1, t_F + 2);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 2, t_F);

					t_Faces[t_F + 2] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F + 1] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F] = t_Faces.back(); t_Faces.pop_back();

					t_Normals[i] = t_Normals.back();
					t_Normals.pop_back();

					i--;
				}
			}

			// NOTE: Work out if the New Faces and the Unique Edges match
			std::vector<size_t> t_NewFaces;
			for (auto [edgeIndex1, edgeIndex2] : t_UniqueEdges)
			{
				t_NewFaces.push_back(edgeIndex1);
				t_NewFaces.push_back(edgeIndex2);
				t_NewFaces.push_back(t_Polytope.size());
			}

			t_Polytope.push_back(t_Support);

			auto [t_NewNormals, t_NewMinimumFace] = GetFaceNormals(t_Polytope, t_NewFaces);

			// NOTE: Check if the Normal is within the distance from the old distance to calculate the normal distance
			float t_OldMinDistance = FLT_MAX;
			for (size_t i = 0; i < t_Normals.size(); i++)
			{
				if (t_Normals[i].w < t_OldMinDistance)
				{
					t_OldMinDistance = t_Normals[i].w;
					t_MinFace = i;
				}
			}

			if (t_NewNormals[t_NewMinimumFace].w < t_OldMinDistance)
			{
				t_MinFace = t_NewMinimumFace + t_Normals.size();
			}

			t_Faces.insert(t_Faces.end(), t_NewFaces.begin(), t_NewFaces.end());
			t_Normals.insert(t_Normals.end(), t_NewNormals.begin(), t_NewNormals.end());
		}
	}

	t_ColMani.collisionNormal = -1 * (t_MinimumNormal.Normalise());
	t_ColMani.penetrationDepth = t_MinimumDistance + 0.01f;
	t_ColMani.hasCollision = true;

	collisionSolutionMap[std::make_pair(epaA, planeB)] = t_ColMani;
	return t_ColMani;
}

CollisionManifold CollisionManager::EPAtoGJK(GameObjectEntity* epaA, GameObjectEntity* gjkB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();
	Simplex t_OutSimplex = Simplex();

	// NOTE: Normal GJK Algorithm
	Vector3 t_Support = Support(epaA, gjkB, Vector3(1, 0, 0));

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = -t_Support;

	// NOTE: Run the GJK Algorithm and Break Out the loop when a simplex is found and store the outsimplex in the out simplex structure
	while (true)
	{
		// NOTE: Check the Collider A and ColliderB Context
		t_Support = Support(epaA, gjkB, t_Direction);

		// NOTE: No Collision
		if (t_Support.Dot(t_Direction) <= 0) { return CollisionManifold(); }

		// NOTE: Check the Simplex that the Collision Lies in
		t_Points.push_front(t_Support);

		if (NextSimplex(t_Points, t_Direction)) { t_OutSimplex = t_Points; break; }
	}


	// NOTE: EPA (Expanding Poltyope Algorithm) Begin
	std::vector<Vector3> t_Polytope(t_OutSimplex.begin(), t_OutSimplex.end());

	// NOTE: Potential Face / Triangle list, in terms of Winding order
	std::vector<size_t> t_Faces = {

		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	// NOTE: n-Polytope of the face, Minimum face normal
	// NOTE: Calculates the new normals of the Face
	auto [t_Normals, t_MinFace] = GetFaceNormals(t_Polytope, t_Faces);

	Vector3 t_MinimumNormal;
	float t_MinimumDistance = FLT_MAX;

	while (t_MinimumDistance == FLT_MAX)
	{
		t_MinimumNormal = t_Normals[t_MinFace].xyz();
		t_MinimumDistance = t_Normals[t_MinFace].w;

		t_Support = Support(epaA, gjkB, t_MinimumNormal);
		float t_Distance = Vector3::S_Dot(t_MinimumNormal, t_Support);

		// NOTE: Calculate the Distance to see if the normal face is within range of the point
		if (abs(t_Distance - t_MinimumDistance) > 0.001f)
		{
			t_MinimumDistance = FLT_MAX;
			std::vector<std::pair<size_t, size_t>> t_UniqueEdges;

			for (int i = 0; i < t_Normals.size(); i++)
			{
				if ((Vector3::S_Dot(t_Normals[i].xyz(), t_Support) - t_Normals[i].w) > 0)
				{
					size_t t_F = i * 3;

					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F, t_F + 1);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 1, t_F + 2);
					AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 2, t_F);

					t_Faces[t_F + 2] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F + 1] = t_Faces.back(); t_Faces.pop_back();
					t_Faces[t_F] = t_Faces.back(); t_Faces.pop_back();

					t_Normals[i] = t_Normals.back();
					t_Normals.pop_back();

					i--;
				}
			}

			// NOTE: Work out if the New Faces and the Unique Edges match
			std::vector<size_t> t_NewFaces;
			for (auto [edgeIndex1, edgeIndex2] : t_UniqueEdges)
			{
				t_NewFaces.push_back(edgeIndex1);
				t_NewFaces.push_back(edgeIndex2);
				t_NewFaces.push_back(t_Polytope.size());
			}

			t_Polytope.push_back(t_Support);

			auto [t_NewNormals, t_NewMinimumFace] = GetFaceNormals(t_Polytope, t_NewFaces);

			// NOTE: Check if the Normal is within the distance from the old distance to calculate the normal distance
			float t_OldMinDistance = FLT_MAX;
			for (size_t i = 0; i < t_Normals.size(); i++)
			{
				if (t_Normals[i].w < t_OldMinDistance)
				{
					t_OldMinDistance = t_Normals[i].w;
					t_MinFace = i;
				}
			}

			if (t_NewNormals[t_NewMinimumFace].w < t_OldMinDistance)
			{
				t_MinFace = t_NewMinimumFace + t_Normals.size();
			}

			t_Faces.insert(t_Faces.end(), t_NewFaces.begin(), t_NewFaces.end());
			t_Normals.insert(t_Normals.end(), t_NewNormals.begin(), t_NewNormals.end());
		}
	}

	t_ColMani.collisionNormal = -1 * (t_MinimumNormal.Normalise());
	t_ColMani.penetrationDepth = t_MinimumDistance + 0.01f;
	t_ColMani.hasCollision = true;

	collisionSolutionMap[std::make_pair(epaA, gjkB)] = t_ColMani;
	return t_ColMani;
}

CollisionManifold CollisionManager::MassAggToMassAgg(GameObjectEntity* massAggA, GameObjectEntity* massAggB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::MassAggToSphere(GameObjectEntity* massAggA, GameObjectEntity* sphereB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	for (int i = 0; i < massAggA->GetComponent<MassAggregate>()->m_MassPoints.size(); ++i)
	{
		Vector3 t_MassAggPosition = massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position;
		const float t_MassAggRadius = massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius;

		Vector3 SphereBPosition = sphereB->m_Transform.m_Position;
		const float SphereBRadius = sphereB->GetComponent<SphereCollider>()->m_Radius;

		float t_Distance = Vector3(t_MassAggPosition - SphereBPosition).Magnitude();
		float t_RadiiSum = t_MassAggRadius + SphereBRadius;

		if (t_Distance <= t_RadiiSum)
		{
			t_ColMani.hasCollision = true;
			t_ColMani.collisionNormal = Vector3(t_MassAggPosition - SphereBPosition).Normalise();
			t_ColMani.penetrationDepth = t_RadiiSum - t_Distance;

			collisionSolutionMap[std::make_pair(massAggA->GetComponent<MassAggregate>()->m_MassPoints[i], sphereB)] = t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::MassAggToPlane(GameObjectEntity* massAggA, GameObjectEntity* planeB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	for (int i = 0; i < massAggA->GetComponent<MassAggregate>()->m_MassPoints.size(); ++i)
	{
		Vector3 t_NearPoint = PlaneNearestPoint(planeB, Vector3(0, 1, 0), massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position);

		float Distance = t_NearPoint.DistanceTo(massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position);

		if (Distance <= massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius)
		{
			t_ColMani.hasCollision = true;
			// t_ColMani.collisionNormal = planeA->GetComponent<PlaneCollider>()->GetNormal();
			t_ColMani.collisionNormal = Vector3(0, 1, 0);
			t_ColMani.penetrationDepth = massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius - 
				Vector3(t_NearPoint - massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position).Magnitude();

			collisionSolutionMap[std::make_pair(massAggA->GetComponent<MassAggregate>()->m_MassPoints[i], planeB)] = t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::MassAggToBox(GameObjectEntity* massAggA, GameObjectEntity* boxB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	CollisionManifold t_ColMani = CollisionManifold();

	for (int i = 0; i < massAggA->GetComponent<MassAggregate>()->m_MassPoints.size(); ++i)
	{
		Vector3 Nearest = BoxNearestPoint(boxB, massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position);
		float Distance = Nearest.DistanceTo(massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position);

		// Check if the Distance of the Circle is in the Box's "Radius"
		if (Distance <= massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius)
		{
			t_ColMani.hasCollision = true;
			t_ColMani.collisionNormal = Vector3(massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position - Nearest).Normalise();
			t_ColMani.penetrationDepth = massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->GetComponent<SphereCollider>()->m_Radius - Vector3(Nearest - massAggA->GetComponent<MassAggregate>()->m_MassPoints[i]->m_Transform.m_Position).Magnitude();

			collisionSolutionMap[std::make_pair(massAggA->GetComponent<MassAggregate>()->m_MassPoints[i], boxB)] = t_ColMani;
		}
	}

	return CollisionManifold();
}

CollisionManifold CollisionManager::MassAggToSAT(GameObjectEntity* massAggA, GameObjectEntity* satB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::MassAggToGJK(GameObjectEntity* massAggA, GameObjectEntity* gjkB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
{
	return CollisionManifold();
}

CollisionManifold CollisionManager::MassAggToEPA(GameObjectEntity* massAggA, GameObjectEntity* epaB, std::map<col_solution_pair, CollisionManifold>& collisionSolutionMap)
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
