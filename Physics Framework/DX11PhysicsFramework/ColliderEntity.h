#ifndef COLLIDER_ENTITY_H
#define COLLIDER_ENTITY_H

#include <iostream>
#include <functional>
#include <unordered_set>

#include "ComponentEntity.h"
#include "OBJLoader.h"
#include "MeshLoader.h"

#include "ConstantBuffer.h"
#include "Geometry.h"
#include "Material.h"

class GameObjectEntity;

enum class TriggerAreaState : std::int8_t
{
    TRIGGER_AREA_STATE_ENTERED,
    TRIGGER_AREA_STATE_STAYED,
    TRIGGER_AREA_STATE_EXITED,
    TRIGGER_AREA_STATE_NONE
};

struct Interval
{
    float Max;
    float Min;

    Interval(float max = 0, float min = 0)
    {
        this->Max = max;
        this->Min = min;
    }
};

class ColliderEntity : public ComponentEntity
{
protected:

    DirectX::XMFLOAT4X4* m_World;

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
    static bool m_RenderCollision;
    bool m_IsTrigger;

    bool m_IsActivated;
    bool m_Quered = false;

    Material m_Material;
    Geometry m_Geometry;

    // TRIGGER AREA VARIABLE(s)
    TriggerAreaState m_TriggerState;


    // COLLIDER VARIABLE(s)
    // ColliderType m_ColliderType;

public: // PUBLIC FUNCTION(s)
   
    // CLASS FUNCTION(s)
    ColliderEntity();
    virtual ~ColliderEntity();

    // BASE FUNCTION(s)
    virtual void Update(float deltaTime) override;
    virtual void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

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
    
};

#endif