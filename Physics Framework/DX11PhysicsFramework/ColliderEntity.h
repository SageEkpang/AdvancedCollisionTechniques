#ifndef COLLIDER_ENTITY_H
#define COLLIDER_ENTITY_H

#include <iostream>
#include <functional>
#include <unordered_set>

#include "ComponentEntity.h"
#include "OBJLoader.h"
#include "MeshLoader.h"

class GameObjectEntity;

enum class TriggerAreaState : std::int8_t
{
    TRIGGER_AREA_STATE_ENTERED,
    TRIGGER_AREA_STATE_STAYED,
    TRIGGER_AREA_STATE_EXITED,
    TRIGGER_AREA_STATE_NONE
};

class ColliderEntity : public ComponentEntity
{
private: // PRIVATE VARIABLE(s)

    std::function<void()> m_TriggerEnteredLambda = nullptr;
    std::function<void()> m_TriggerStayedLambda = nullptr;
    std::function<void()> m_TriggerExitedLambda = nullptr;

    std::unordered_set<GameObjectEntity*> m_ObjectList;
    std::unordered_set<GameObjectEntity*>::iterator m_ObjectItr;

public: // PUBLIC VARIABLE(s)

    // BASE VARIABLE(s)
    bool m_HasCollided = false;
    bool m_IsCollideable = true;
    bool m_RenderCollision = true;
    bool m_IsTrigger;

    bool m_IsActivated;
    bool m_Quered = false;

    Material m_Material;
    Geometry m_Geometry;

    // TRIGGER AREA VARIABLE(s)
    TriggerAreaState m_TriggerState;

    std::vector<Vector3> m_Vertices;
    std::vector<Vector3> m_PositionStore;

    // COLLIDER VARIABLE(s)
    // ColliderType m_ColliderType;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    ColliderEntity();
    virtual ~ColliderEntity();

    // BASE FUNCTION(s)
    void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

    // HELPER FUNCTION(s)
    void TriggerQuery(GameObjectEntity* gameObject);
    void TriggerEnteredExecute(std::function<void()> func = nullptr);
    void TriggerStayedExecute(std::function<void()> func = nullptr);
    void TriggerExitedExecute(std::function<void()> func = nullptr);
    void TriggerQueryExecute();

    // GETTER FUNCTION(s)
    auto GetTriggerObject() { return (*m_ObjectItr); }
    inline std::unordered_set<GameObjectEntity*>& GetObjects() { return m_ObjectList; }
    inline int GetObjectCount() { return (int)m_ObjectList.size(); }


    void SetCollisionGeometry(char* fileName, Material material, ID3D11Device* device);

    // HELPER
    Vector3 FindFurthestPoint(Vector3 direction); // GJK Algo Function
    /*Vector3 SphereNearestPoint(Vector3 point);*/

    // TODO: Make a function that updates the verticese within this field
    /// <summary> NOTE: This needs to take a file path for computing the points to draw </summary>
    // void FillVerticesArray(char* path, Transform* objectTransform);
    // SETTER FUNCTION(s)

};

#endif