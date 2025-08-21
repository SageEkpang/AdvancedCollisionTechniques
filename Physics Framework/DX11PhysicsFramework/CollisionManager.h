#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "GameObjectEntity.h"
#include "ColliderEntity.h"
#include "CollisionManifold.h"
#include <utility>
#include <map>

#include <typeindex>
#include <typeinfo>

class BoxCollider;
class SphereCollider;
class PlaneCollider;

class SATCollider;
class EPACollider;
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

    // COMPLEX COLLIUSION(s)
    COLLIDER_TYPE_COLLISIONS_SAT_TO_SAT,
    COLLIDER_TYPE_COLLISIONS_EPA_TO_EPA,
    COLLIDER_TYPE_COLLISIONS_GJK_TO_GJK
};

class CollisionManager
{
private:

    typedef std::pair<std::type_index, std::type_index> col_type_pair;
    std::map<col_type_pair, Collider_Type_Collisions> m_CollisionMapping;

public:

    // CLASS FUNCTION(s)
    CollisionManager();
    ~CollisionManager();

    // COLLIDER FUNCTIONS
    CollisionManifold CheckCollisions(GameObjectEntity* colliderA, GameObjectEntity* colliderB);

    // SPHERE
    static CollisionManifold SphereToSphere(GameObjectEntity* sphereA, GameObjectEntity* sphereB);

    // BOX
    static CollisionManifold BoxToBox(GameObjectEntity* boxA, GameObjectEntity* boxB);
    static CollisionManifold BoxToSphere(GameObjectEntity* boxA, GameObjectEntity* sphereB);

    // PLANE
    static CollisionManifold PlaneToPlane(GameObjectEntity* planeA, GameObjectEntity* planeB);
    static CollisionManifold PlaneToBox(GameObjectEntity* planeA, GameObjectEntity* boxB);
    static CollisionManifold PlaneToSphere(GameObjectEntity* planeA, GameObjectEntity* sphereB);
    
    // SAT
    static CollisionManifold SATtoSAT(GameObjectEntity* satA, GameObjectEntity* satB);

    // GJK
    static CollisionManifold GJKtoGJK(GameObjectEntity* gjkA, GameObjectEntity* gjkB);

    // EPA
    static CollisionManifold EPAtoEPA(GameObjectEntity* epaA, GameObjectEntity* epaB);


    // NEAREST POINT CHECKS
    static Vector3 BoxNearestPoint(GameObjectEntity* boxA, Vector3 pointB);
    static bool PointInBox(GameObjectEntity* boxA, Vector3 pointB);

    static Vector3 SphereNearestPoint(GameObjectEntity* sphereA, Vector3 pointB);
    static bool PointInSphere(GameObjectEntity* sphereA, Vector3 pointB);

    static Vector3 PlaneNearestPoint(GameObjectEntity* planeA, Vector3 planeNormal, Vector3 pointB);
    static bool PointInPlane(GameObjectEntity* planeA, Vector3 planeNormal, Vector3 pointB);
};

#endif