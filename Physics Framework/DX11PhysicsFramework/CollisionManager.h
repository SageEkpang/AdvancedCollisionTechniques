#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "GameObjectEntity.h"
#include "ColliderEntity.h"
#include "CollisionManifold.h"
#include "Simplex.h"
#include "Vector4.h"
#include <utility>
#include <map>

#include <typeindex>
#include <typeinfo>

class BoxCollider;
class SphereCollider;
class PlaneCollider;

class SATCollider;
class EPACollider;
class MassAggregate;
class GJKCollider;

enum Collider_Type_Collisions
{
    // SIMPLE COLLISION(s)
    COLLIDER_TYPE_COLLISIONS_SPHERE_TO_SPHERE = 1,

    COLLIDER_TYPE_COLLISIONS_BOX_TO_BOX,
    COLLIDER_TYPE_COLLISIONS_BOX_TO_SPHERE,

    COLLIDER_TYPE_COLLISIONS_PLANE_TO_PLANE,
    COLLIDER_TYPE_COLLISIONS_PLANE_TO_BOX,
    COLLIDER_TYPE_COLLISIONS_PLANE_TO_SPHERE,

    // COMPLEX COLLISION(s)
    COLLIDER_TYPE_COLLISIONS_SAT_TO_SAT,
    COLLIDER_TYPE_COLLISIONS_SAT_TO_BOX,

    COLLIDER_TYPE_COLLISIONS_EPA_TO_EPA,

    COLLIDER_TYPE_COLLISIONS_GJK_TO_GJK,

    COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_SPHERE,
    COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_PLANE,
    COLLIDER_TYPE_COLLISIONS_MASS_AGG_TO_BOX
};

class CollisionManager
{
private:

    typedef std::pair<std::type_index, std::type_index> col_type_pair;
    std::map<col_type_pair, Collider_Type_Collisions> m_CollisionMapping;

    static bool CollisionOverlapAxis(GameObjectEntity* satA, GameObjectEntity* boxB, Vector3 axis);

public:

    // HELPER FUNCTION(s)
    // GJK
        static bool Line(Simplex& points, Vector3& direction);
        static bool Triangle(Simplex& points, Vector3& direction);
        static bool Tetrahedron(Simplex& points, Vector3& direction);
        static bool SameDirection(const Vector3& direction, const Vector3& ao);

        static Vector3 SupportGJK(GameObjectEntity* colliderA, GameObjectEntity* colliderB, Vector3 direction);
        static Vector3 SupportEPA(GameObjectEntity* colliderA, GameObjectEntity* colliderB, Vector3 direction);

        static bool NextSimplex(Simplex& points, Vector3& direction);

        static Vector3 FindFurthestPointGJK(GameObjectEntity* gjkA, Vector3 direction);
        static Vector3 FindFurthestPointEPA(GameObjectEntity* epaA, Vector3 direction);

    // EPA
        static void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t>& faces, size_t a, size_t b);
        static std::pair<std::vector<Vector4>, size_t> GetFaceNormals(std::vector<Vector3>& polytope, std::vector<size_t>& faces);





    // CLASS FUNCTION(s)
    CollisionManager();
    ~CollisionManager();

    // COLLIDER FUNCTIONS
    CollisionManifold CheckCollisions(GameObjectEntity* colliderA, GameObjectEntity* colliderB);

    // SPHERE
    static CollisionManifold SphereToSphere(GameObjectEntity* sphereA, GameObjectEntity* sphereB);
    static CollisionManifold S_SphereToSphere(Vector3 sphereAPos, float sphereARadius, Vector3 sphereBPos, float sphereBRadius);

    // BOX
    static CollisionManifold BoxToBox(GameObjectEntity* boxA, GameObjectEntity* boxB);
    static CollisionManifold BoxToSphere(GameObjectEntity* boxA, GameObjectEntity* sphereB);

    // PLANE
    static CollisionManifold PlaneToPlane(GameObjectEntity* planeA, GameObjectEntity* planeB);
    static CollisionManifold PlaneToBox(GameObjectEntity* planeA, GameObjectEntity* boxB);
    static CollisionManifold PlaneToSphere(GameObjectEntity* planeA, GameObjectEntity* sphereB);
    
    // SAT
    static CollisionManifold SATtoSAT(GameObjectEntity* satA, GameObjectEntity* satB);
    static CollisionManifold SATtoBox(GameObjectEntity* satA, GameObjectEntity* boxB);

    // GJK
    static CollisionManifold GJKtoGJK(GameObjectEntity* gjkA, GameObjectEntity* gjkB);

    // EPA
    static CollisionManifold EPAtoEPA(GameObjectEntity* epaA, GameObjectEntity* epaB);

    // MassAggregate
    static CollisionManifold MassAggToSphere(GameObjectEntity* massAggA, GameObjectEntity* planeB);
    static CollisionManifold MassAggToPlane(GameObjectEntity* massAggA, GameObjectEntity* planeB);
    static CollisionManifold MassAggToBox(GameObjectEntity* massAggA, GameObjectEntity* planeB);


    // NEAREST POINT CHECKS
    static Vector3 BoxNearestPoint(GameObjectEntity* boxA, Vector3 pointB);
    static bool PointInBox(GameObjectEntity* boxA, Vector3 pointB);

    static Vector3 SphereNearestPoint(GameObjectEntity* sphereA, Vector3 pointB);
    static bool PointInSphere(GameObjectEntity* sphereA, Vector3 pointB);

    static Vector3 PlaneNearestPoint(GameObjectEntity* planeA, Vector3 planeNormal, Vector3 pointB);
    static bool PointInPlane(GameObjectEntity* planeA, Vector3 planeNormal, Vector3 pointB);
};

#endif