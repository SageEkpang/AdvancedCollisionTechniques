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

Vector3 SphereCollider::NearestPoint(Vector3 point) // Point and Sphere
{
    Vector3 t_SphereToPoint = Vector3::S_Normalise(point - (m_Owner->m_Transform.m_Position + m_Offset));
    t_SphereToPoint *= m_Radius;
    return t_SphereToPoint + (m_Owner->m_Transform.m_Position + m_Offset);
}

bool SphereCollider::PointInSphere(Vector3 point)
{
    float t_MagnitudeSquared = std::pow(Vector3::S_Magnitude(point - (m_Owner->m_Transform.m_Position + m_Offset)), 2);
    float t_RadiusAmount = m_Radius * m_Radius;
    return t_MagnitudeSquared < t_RadiusAmount;
}


