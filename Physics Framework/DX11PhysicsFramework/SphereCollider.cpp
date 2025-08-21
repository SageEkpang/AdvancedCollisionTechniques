#include "SphereCollider.h"
#include "GameObjectEntity.h"

SphereCollider::SphereCollider(Vector3 offset, float radius)
{
    m_Offset = offset;
    m_Radius = radius;
}

SphereCollider::SphereCollider(float x_offset, float y_offset, float z_offset, float radius)
{
    m_Offset = Vector3(x_offset, y_offset, z_offset);
    m_Radius = radius;
}

SphereCollider::SphereCollider(float radius)
{
    m_Offset = Vector3(0, 0, 0);
    m_Radius = radius;
}

SphereCollider::SphereCollider()
{
    m_Offset = Vector3(0, 0, 0);
    m_Radius = 1.f;
}

void SphereCollider::Construct(Vector3 offset, float radius)
{
    m_Offset = offset;
    m_Radius = radius;
}

void SphereCollider::Construct(float x_offset, float y_offset, float z_offset, float radius)
{
    m_Offset = Vector3(x_offset, y_offset, z_offset);
    m_Radius = radius;
}

void SphereCollider::Construct(float radius)
{
    m_Offset = Vector3(0, 0, 0);
    m_Radius = radius;
}


